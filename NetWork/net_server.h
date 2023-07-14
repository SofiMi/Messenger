#pragma once
#include <thread>
#include <asio.hpp>
#include "net_deque.h"
#include "message.h"

template <typename T>
class net_server {
 protected:
  size_t count_client;
  net_deque <owned_message<T>> queue_from;
  asio::io_context context;
  std::thread thrContext;
 public:
  net_server();
  virtual ~net_server();
  bool Start();
  void Stop();
  void WaitClient();
  void Send(std::shared_ptr<connection<T>> client, const message& msg);
  void SendAll(const message& msg);
};  