#pragma once
#include "../include.h"
#include "net_server.h"
#include "../DBWork/data_base.h"
#include <unordered_map>
#include <tuple>
#include <string>

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
  void LastMessageId(std::shared_ptr<net::connection<msg_type>> nnection_cl, net::message<msg_type>& message);
  void NewMessage(std::shared_ptr<net::connection<msg_type>> nnection_cl, net::message<msg_type>& message);
  void AddNewUser(std::shared_ptr<net::connection<msg_type>> connection_cl, net::message<msg_type>& message);
  void CheckUniqueNick(std::shared_ptr<net::connection<msg_type>> connection_cl, net::message<msg_type>& message);
  void CheckUniqueLogin(std::shared_ptr<net::connection<msg_type>> connection_cl, net::message<msg_type>& message);
  void CheckChatName(std::shared_ptr<net::connection<msg_type>> connection_cl, net::message<msg_type>& message);
  void CreateNewChat(std::shared_ptr<net::connection<msg_type>> connection_cl, net::message<msg_type>& message);
  void CheckTetAtTetChat(std::shared_ptr<net::connection<msg_type>> connection_cl, net::message<msg_type>& message);
  void GetDataUpdate(std::shared_ptr<net::connection<msg_type>> connection_cl, net::message<msg_type>& input_message);
  void GetLastMsgId(std::shared_ptr<net::connection<msg_type>> connection_cl, net::message<msg_type>& input_message);
  void GetName(std::shared_ptr<net::connection<msg_type>> connection_cl, net::message<msg_type>& input_message);

  void SendManyMsg(std::shared_ptr<net::connection<msg_type>> connection_cl, uint32_t send_more, uint32_t finish, pqxx::result& texts);

  std::unordered_map<int, std::tuple<int, int, std::string, std::shared_ptr<net::connection<msg_type>>>> user_messages_memory_; // <userid, <chatid, size_message (оставшаяся), message>>
  int MESSAGE_BUFFER_SIZE = 254;
};