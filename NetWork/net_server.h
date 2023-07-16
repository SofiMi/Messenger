#pragma once
#include "message.h"
#include "net_deque.h"
#include <asio.hpp>
#include <thread>

template <typename T> 
class net_server {
 public:
  net_server(uint port);
  virtual ~net_server();
  void Stop();
  bool Start();
  void WaitForClientConnection();
  void MessageClient(std::shared_ptr<connection<T>> client,
                    const message<T> &msg);
  void MessageAllClients(const message<T> &msg, std::shared_ptr<connection<T>> pIgnoreClient = nullptr);
  void Update(size_t nMaxMessages = -1, bool bWait = false);

  virtual void OnClientValidated(std::shared_ptr<connection<T>> client) {}

protected:
  asio::io_context context_;
  std::thread thread_;
  asio::ip::tcp::acceptor acceptor_;

  std::deque<std::shared_ptr<connection<T>>> deque_connection_;
  tsqueue<owned_message<T>> deque_messages_;
  uint32_t nIDCounter = 10000;

  virtual bool OnClientConnect(std::shared_ptr<connection<T>> client) { return false; }
  virtual void OnClientDisconnect(std::shared_ptr<connection<T>> client) {}
  virtual void OnMessage(std::shared_ptr<connection<T>> client, message<T> &msg) {}
};

template <typename T>
void net_server<T>::Stop() {
  context_.stop();
  if (thread_.joinable())
    thread_.join();
  std::cout << "[SERVER] Stopped!\n";
}

template <typename T>
bool net_server<T>::Start() {
  try {
    WaitForClientConnection();
    thread_ = std::thread([this]() { context_.run(); });
  } catch (std::exception &e) {
    std::cerr << "[SERVER] Exception: " << e.what() << "\n";
    return false;
  }
  std::cout << "[SERVER] Started!\n";
  return true;
}

template <typename T>
void net_server<T>::WaitForClientConnection() {
  acceptor_.async_accept(
    [this](std::error_code ec, asio::ip::tcp::socket socket) {
    if (!ec) {
      std::cout << "[SERVER] New Connection: " << socket.remote_endpoint() << std::endl;
      std::shared_ptr<connection<T>> newconn =
          std::make_shared<connection<T>>(connection<T>::owner::server,
                                          context_, std::move(socket),
                                          deque_messages_);

      if (OnClientConnect(newconn)) {
        // Пользователь согласился подключиться к серверу
        deque_connection_.push_back(std::move(newconn));
        deque_connection_.back()->ConnectToClient(this, nIDCounter++);

        std::cout << "[" << deque_connection_.back()->GetID()
                  << "] Connection Approved\n";
      } else {
        std::cout << "[-----] Connection Denied\n";
      }
    } else {
      std::cout << "[SERVER] New Connection Error: " << ec.message() << "\n";
    }
    WaitForClientConnection();
  });
}

template <typename T>
void net_server<T>::MessageClient(std::shared_ptr<connection<T>> client, const message<T> &msg) {
  if (client && client->IsConnected()) {
    client->Send(msg);
  } else {
    OnClientDisconnect(client);
    client.reset();
    deque_connection_.erase(std::remove(deque_connection_.begin(), deque_connection_.end(), client), deque_connection_.end());
  }
}

template <typename T>
void net_server<T>::MessageAllClients(const message<T> &msg, std::shared_ptr<connection<T>> pIgnoreClient) {
  bool bInvalidClientExists = false;

  for (auto& client : deque_connection_) {
    if (client && client->IsConnected()) {
      if (client != pIgnoreClient)
        client->Send(msg);
    } else {
      OnClientDisconnect(client);
      client.reset();
      bInvalidClientExists = true;
    }
  }

  if (bInvalidClientExists)
    deque_connection_.erase(std::remove(deque_connection_.begin(),
                                        deque_connection_.end(), nullptr),
                            deque_connection_.end());
}

template <typename T>
net_server<T>::net_server(uint port) : acceptor_(context_, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)) {}

template <typename T>
net_server<T>::~net_server() {
  Stop();
}

template <typename T>
void net_server<T>::Update(size_t nMaxMessages, bool bWait) {
  if (bWait)
    deque_messages_.wait();

  size_t nMessageCount = 0;
  while (nMessageCount < nMaxMessages && !deque_messages_.empty()) {
    auto msg = deque_messages_.pop_front();
    OnMessage(msg.remote, msg.msg);
    nMessageCount++;
  }
}