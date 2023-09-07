#ifndef NET_CONNECTION
#define NET_CONNECTION

#include "net_queue.h"
#include "net_message.h"

#include <memory>
#include <thread>
#include <mutex>
#include <deque>
#include <string>
#include <iostream>
#include <chrono>
#include <limits>
#include <array>

#define ASIO_STANDALONE
#include <boost/asio.hpp>

using boost::asio::ip::tcp;


namespace net {
  template <typename T>
  class connection : public std::enable_shared_from_this<connection<T>> {
  public:
    enum class owner {
      server,
      client
    };

  public:
    connection(owner parent, boost::asio::io_context &asioContext, boost::asio::ip::tcp::socket socket, ts_queue<owned_message<T>> &qIn)
        : __io_context(asioContext), __socket(std::move(socket)), __q_messages_in(qIn)
    {
      __owerner_type = parent;
    }

    virtual ~connection()
    {
    }

    uint32_t get_id() const
    {
      return id;
    }

  public:
    void connect_to_client(uint32_t uid = 0)
    {
      if (__owerner_type == owner::server) {
        if (__socket.is_open()) {
          id = uid;
          read_data();
        }
      }
    }

    void connect_to_server(const tcp::resolver::results_type &endpoints)
    {
      if (__owerner_type == owner::client) {
        boost::asio::async_connect(__socket, endpoints,
                                   [this](std::error_code ec, tcp::endpoint endpoint) {
                                     if (!ec)
                                       read_data();
                                   });
      }
    }


    void disconnect()
    {
      if (is_connected())
        boost::asio::post(__io_context, [this]() { __socket.close(); });
    }

    bool is_connected() const
    {
      return __socket.is_open();
    }

    void start_listening()
    {
    }

  public:
    void send(const message<T> &msg)
    {
      boost::asio::post(__io_context,
                        [this, msg]() {
                          // Если в очереди есть сообщение, то мы должны
                          // предположим, что он находится в процессе асинхронной записи.
                          // В любом случае добавьте сообщение в очередь для вывода. Если нет сообщений
                          // были доступны для записи, то начинаем процесс записи
                          // сообщение в начале очереди.
                          bool bWritingMessage = !__q_messages_out.empty();
                          try {
                            //std::cout << "SEND MSG" << std::endl;
                            __q_messages_out.push_back(msg);
                          } catch (std::exception &e) {
                            std::cerr << "post exception: " << e.what() << '\n';
                          }
                          if (!bWritingMessage) {
                            write_data();
                          }
                        });
    }



  private:
    void write_data() {
      // Если эта функция вызывается, мы знаем, что очередь исходящих сообщений должна иметь
      // по крайней мере одно сообщение для отправки. Поэтому выделите буфер передачи для хранения
      // сообщение, и выдаем работу - asio, отправляем эти байты
      boost::asio::async_write(__socket, boost::asio::buffer(&__q_messages_out.front(), sizeof(message<T>)),
                               [this](std::error_code ec, std::size_t length) {
                                 if (!ec) {
                                   __q_messages_out.pop_front();

                                   if (!__q_messages_out.empty())
                                     write_data();
                                 }
                                 else {
                                   std::cerr << "[" << id << "] Write Data Fail.\n";
                                   __socket.close();
                                 }
                               });
    }

    void read_data() {
      // Если эта функция вызывается, мы ожидаем, что asio будет ждать, пока не получит
      // достаточно байтов для формирования заголовка сообщения. Мы знаем, что заголовки являются фиксированными
      // размер, поэтому выделите достаточно большой буфер передачи для его хранения. Фактически,
      // мы создадим сообщение во "временном" объекте сообщения, поскольку оно
      // удобно работать.
      boost::asio::async_read(__socket, boost::asio::buffer(&__temp_msg_in, sizeof(message<T>)),
                              [this](std::error_code ec, std::size_t length) {
                                if (!ec) {
                                  add_to_incomming_message_queue();
                                }
                                else {
                                  std::cerr << "[" << id << "] Leave the server...\n";
                                  __socket.close();
                                }
                              });
    }

    void add_to_incomming_message_queue() {
      if (__owerner_type == owner::server)
        __q_messages_in.push_back({ this->shared_from_this(), __temp_msg_in });
      else
        __q_messages_in.push_back({ nullptr, __temp_msg_in });
      read_data();
    }

  protected:
    tcp::socket __socket;
    boost::asio::io_context &__io_context;
    ts_queue<message<T>> __q_messages_out;
    ts_queue<owned_message<T>> &__q_messages_in;
    message<T> __temp_msg_in;
    owner __owerner_type = owner::server;
    uint32_t id = 0;
  };
}    // namespace net
#endif