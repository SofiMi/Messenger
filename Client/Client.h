#pragma once
#include "net_client.h"
#include "../include.h"
#include <vector>
#include <string>

class Client : public net::client_interface<msg_type> {
 private:
  std::array<char, 256> user_name{};
  uint32_t userid_;
  int chatid_ = 1;
  int count_chats_ = 0;
  int message_index_ = 20;
  int size_msg_last_ = 0;
 public:
  void CheckLogin(const std::string& login);
  void CheckPassword(const std::string& password);

  void CheckUpdateByIdChat(size_t id);
  void send_msg(std::string& __data);
  void SetUserid(uint32_t userid);
  std::vector<std::pair<int, std::string>> GetChats();
  std::vector<std::string> GetMessage(size_t count);

  std::string GetName() const { return user_name.data(); }
};
