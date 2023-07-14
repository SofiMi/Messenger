#pragma once
#include <thread>
#include <asio.hpp>
#include "net_deque.h"
#include "message.h"

template <typename T>
class net_client {
 protected:
  net_deque <owned_message<T>> user_queue;
  asio::io_context context;
  std::thread thrContext;
  asio::ip::tcp::socket socket;
  std::unique_ptr<connection<T>> cl_connection;
 public:
  net_client();
  virtual ~net_client();
  bool Connect(const std::string& host, const uint16_t port);
  void Disconnect();
  bool IsConnected();
};  