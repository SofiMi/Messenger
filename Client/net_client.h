#ifndef NET_CLIENT
#define NET_CLIENT

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
  class client_interface {
  public:
    client_interface() {}
    virtual ~client_interface() { disconnect(); }

  public:
    bool connect(const std::string &host, const uint16_t port) {
      try {
        tcp::resolver resolver(__io_context);
        tcp::resolver::results_type endpoints = resolver.resolve(host, std::to_string(port));

        connect_ptr = std::make_unique<connection<T>>(connection<T>::owner::client, __io_context, tcp::socket(__io_context), __q_messages_in);
        connect_ptr->connect_to_server(endpoints);

        thrContext = std::thread([this]() { __io_context.run(); });
        std::cerr << "leave connect function\n";
      } catch (std::exception &e) {
        std::cerr << "Client Exception: " << e.what() << '\n';
        return false;
      }
      return true;
    }

    void disconnect() {
      if (is_connected()) {
        connect_ptr->disconnect();
      }

      __io_context.stop();
      if (thrContext.joinable())
        thrContext.join();

      connect_ptr.release();
    }

    bool is_connected() {
      if (connect_ptr)
        return connect_ptr->is_connected();
      else
        return false;
    }

  public:
    void send(const message<T> &msg) {
      if (is_connected())
        connect_ptr->send(msg);
    }

    ts_queue<owned_message<T>> &get_in_comming()
    {
      return __q_messages_in;
    }

  protected:
    boost::asio::io_context __io_context;
    std::thread thrContext;
    std::unique_ptr<connection<T>> connect_ptr;

  private:
    ts_queue<owned_message<T>> __q_messages_in;
  };
}    // namespace net

#endif