#pragma once
#include "message.h"
#include "net_deque.h"
#include <asio.hpp>
#include <thread>

template <typename T>
class net_client {
 public:
  net_client() {}
  virtual ~net_client() { Disconnect(); }
  bool Connect(const std::string &host, const uint16_t port);
  void Disconnect();
  bool IsConnected();
  void Send(const message<T> &msg);
  tsqueue<owned_message<T>> &Incoming() { return input_deque_; }

 protected:
  asio::io_context context_;
  std::thread thread_;
  std::unique_ptr<connection<T>> connection_;

 private:
  tsqueue<owned_message<T>> input_deque_;
};

template <typename T>
bool net_client<T>::Connect(const std::string& host, const uint16_t port) {
  try {
    asio::ip::tcp::resolver resolver(context_);
    asio::ip::tcp::resolver::results_type endpoints =
        resolver.resolve(host, std::to_string(port));

    connection_ = std::make_unique<connection<T>>(
        connection<T>::owner::client, context_,
        asio::ip::tcp::socket(context_), input_deque_);
    connection_->ConnectToServer(endpoints);
    thread_ = std::thread([this]() { context_.run(); });
  } catch (std::exception &e) {
    std::cerr << "Client Exception: " << e.what() << "\n";
    return false;
  }
  return true;
}

template <typename T>
void net_client<T>::Disconnect() {
  if (IsConnected()) {
    connection_->Disconnect();
  }

  context_.stop();
  if (thread_.joinable())
    thread_.join();

  connection_.release();
}

template <typename T>
bool net_client<T>::IsConnected() {
  if (connection_)
    return connection_->IsConnected();
  else
    return false;
}

template <typename T>
void net_client<T>::Send(const message<T> &msg) {
  if (IsConnected())
    connection_->Send(msg);
}