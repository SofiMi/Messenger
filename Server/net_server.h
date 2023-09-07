#ifndef NET_SERVER
#define NET_SERVER

#include "../NetWork/net_message.h"
#include "../NetWork/net_queue.h"
#include "../NetWork/net_connection.h"

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
  class server_interface {
  public:
    server_interface(uint16_t port)
        : __acceptor(__io_context, tcp::endpoint(tcp::v4(), port)) {}

    virtual ~server_interface() { stop(); }

  public:
    bool start()
    {
      try {
        wait_for_client_connection();
        __context_thread = std::thread([this]() { __io_context.run(); });
      } catch (std::exception &excp) {
        std::cerr << "[SERVER] Exception: " << excp.what() << '\n';
        return false;
      }

      std::cout << "[SERVER MESSAGE] Server started...\n";
      return true;
    }

    void stop()
    {
      __io_context.stop();
      if (__context_thread.joinable())
        __context_thread.join();

      std::cout << "[SERVER] Server stopped...\n";
    }

    void wait_for_client_connection() {
      __acceptor.async_accept([this](std::error_code err, tcp::socket socket) {
        if (!err) {
          std::cout << "[SERVER MESSAGE] Server Get New Connection\n";

          std::shared_ptr<connection<T>> new_connect =
            std::make_shared<connection<T>>(connection<T>::owner::server, __io_context, std::move(socket), __q_messages_in);

          if (__on_client_connect(new_connect)) {
            __connection_deq.push_back(std::move(new_connect));
            __connection_deq.back()->connect_to_client(__io_counter++);
          } else {
            std::cout << "[-----] Connection Denied...!\n";
          }
        }
        else {
          std::cout << "[SERVER] Connection Error: " << err.message() << '\n';
        }

        wait_for_client_connection();
      });
    }

    void message_client(std::shared_ptr<connection<T>> client, const message<T> &msg) {
      if (client && client->is_connect()) {
        client->send(msg);
      } else {
        __on_client_disconnect(client);
        client.reset();
        __connection_deq.erase(
          std::remove(__connection_deq.begin(), __connection_deq.end(), client), __connection_deq.end());
      }
    }

    void message_all_clients(const message<T> &msg, std::shared_ptr<connection<T>> ignored_client = nullptr) {
      bool invalid_client_exists = false;

      for (auto &__client : __connection_deq) {
        if (__client && __client->is_connected()) {
          if (__client != ignored_client)
            __client->send(msg);
        } else {
          __on_client_disconnect(__client);
          __client.reset();
          invalid_client_exists = true;
        }
      }

      if (invalid_client_exists)
        __connection_deq.erase(std::remove(__connection_deq.begin(), __connection_deq.end(), nullptr), __connection_deq.end());
    }

    void update(std::size_t max_messages = -1, bool __wait = false) {
      if (__wait)
        __q_messages_in.wait();

      std::size_t __message_count = 0;
      while (__message_count < max_messages && !__q_messages_in.empty()) {
        auto msg = __q_messages_in.pop_front();
        __on_message(msg.remote, msg.msg);
        __message_count++;
      }
    }

  protected:
    virtual bool __on_client_connect(std::shared_ptr<connection<T>> client) {
      return true;
    }

    virtual void __on_client_disconnect(std::shared_ptr<connection<T>> client){
      std::cout << "Removing client [" << client->get_id() << "] \n";
    }

    virtual void __on_message(std::shared_ptr<connection<T>> client, message<T> &msg) {}


  protected:
    ts_queue<owned_message<T>> __q_messages_in;
    std::deque<std::shared_ptr<connection<T>>> __connection_deq;
    boost::asio::io_context __io_context;
    std::thread __context_thread;
    tcp::acceptor __acceptor;
    uint32_t __io_counter = 0;
  };
}    // namespace net

#endif