#include "./NetWork/message.h"
#include "./NetWork/net_client.h"
#include "./NetWork/net_server.h"
#include "./NetWork/net_deque.h"
#include "./NetWork/net_connection.h"

int main() {
  message msg;
  message msg2;
  //connection<int> a;
  msg2.AddInfo(5);
  msg2.AddInfo(9.0);
  return 0;
}