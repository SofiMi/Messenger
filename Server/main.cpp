int SERVER_PORT = 20000;
#include "Server.h"

int main() {
  Server server(SERVER_PORT);
  server.start();

  while (server.server_do) {
    server.update(-1);
  }

  return 0;
}