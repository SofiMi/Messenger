#include "../../Client/net_client.h"
#include "../../include.h"

class Killer : public net::client_interface<msg_type> {
  public:
    void kill() {
      net::message<msg_type> message;
      message.header.id = msg_type::StopServer;
      send(message);
    }
};

int main() {
  Killer killer;
  killer.connect("127.0.0.1", 10030);
  if (!killer.is_connected()) {
    std::cout << "No connection\n" << std::endl;
    throw;
  }

  while (killer.is_connected()) {
    killer.kill();
  }
}