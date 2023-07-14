#pragma once
#include <asio.hpp>
#include "net_deque.h"

class message;

template <typename T>
class owned_message;

template <typename T>
class connection : public std::enable_shared_from_this<connection<T>> {
 protected:
  asio::io_context& asio_context; // by net_server
  asio::ip::tcp::socket conn_socket;

  net_deque<message> conn_queue;
  net_deque<owned_message<T>>& user_queue;
 public :
  connection();
  virtual ~connection();
  bool ConnectToServer();
  bool Disconnect();
  bool IsConnected() const;
  bool Send(const message& msg);
}; 