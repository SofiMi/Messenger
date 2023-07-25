int SERVER_PORT = 10030;
#include "Server.h"

int main() {
  Server server(SERVER_PORT);
  server.start();

  while (server.server_do) {
    server.update(-1);
  }

  return 0;
}