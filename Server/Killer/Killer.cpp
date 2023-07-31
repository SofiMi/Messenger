#include "../../include.h"
#include "../../NetWork/net_message.h"
#include "../../NetWork/net_connection.h"
#include <iostream>
#include <thread>
#include <memory>

class Killer {
  public:
    void kill() {
      net::message<msg_type> message;
      message.header.id = msg_type::StopServer;
      send(message);
    }

    ~Killer() { disconnect(); }
    
    bool connect(const std::string& host, const uint16_t port) {
      try {
      boost::asio::ip::tcp::resolver resolver(asio_context);
      boost::asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(host, std::to_string(port));

      server_connection = std::make_unique<net::connection<msg_type>>(net::connection<msg_type>::owner::client, asio_context,
                                                                      boost::asio::ip::tcp::socket(asio_context), message_queue);
      server_connection->connect_to_server(endpoints);

      thr = std::thread([this]() { asio_context.run(); });
    } catch (std::exception &ex) {
      std::cerr << "Client Exception: " << ex.what() << '\n';
      return false;
    }
    return true;
  }
  
  void disconnect() {
    if (is_connected()) {
      server_connection->disconnect();
    }

    asio_context.stop();
    if (thr.joinable())
      thr.join();

    server_connection.release();
  }

  bool is_connected() {
    return server_connection ? server_connection->is_connected() : false;
  }

  void send(const net::message<msg_type>& message) {
    if (is_connected()) {
      server_connection->send(message);
    }
  }

  boost::asio::io_context asio_context;
  std::thread thr;
  std::unique_ptr<net::connection<msg_type>> server_connection;
  net::ts_queue<net::owned_message<msg_type>> message_queue;
};

int main() {
  Killer killer;
  killer.connect("127.0.0.1", 20000);
  if (!killer.is_connected()) {
    std::cout << "No connection\n" << std::endl;
    throw;
  }

  while (killer.is_connected()) {
    killer.kill();
  }
}