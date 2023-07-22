#pragma once
#include "../include.h"
#include "net_server.h"
#include "../DBWork/data_base.h"

class Server : public net::server_interface<msg_type> {
public:
  bool server_do = true;
  Server(uint16_t port) : net::server_interface<msg_type>(port) {}
  void SendImg(std::shared_ptr<net::connection<msg_type>> client);
  WorkDB db;

protected:
  virtual void __on_message(std::shared_ptr<net::connection<msg_type>> client,
                            net::message<msg_type> &msg) override;
private:
  void CheckPassword(std::shared_ptr<net::connection<msg_type>> connection_cl, net::message<msg_type>& message);
  void CheckLogin(std::shared_ptr<net::connection<msg_type>> connection_cl, net::message<msg_type>& message);
  void GetChat(std::shared_ptr<net::connection<msg_type>> connection_cl, net::message<msg_type>& message);
  void GetMessages(std::shared_ptr<net::connection<msg_type>> connection_cl, net::message<msg_type>& message);
  void LastMessageId(std::shared_ptr<net::connection<msg_type>> connection_cl, net::message<msg_type>& message);
};