#pragma once
#include "net_client.h"
#include "../include.h"
#include <vector>
#include <string>

class Client : public net::client_interface<msg_type> {
 private:
  std::array<wchar_t, 256> user_name{};
  size_t userid_;
  bool GetNamebyServer();
 public:
  void join_server();
  void CheckLogin(const std::wstring& login);
  void CheckPassword(const std::wstring& password);
  void StopServer();
  void send_msg(std::wstring& __data);
  void SetUserid(int userid);
  std::vector<std::string> GetFriend(size_t count, bool& other_fr);
  std::vector<std::string> GetMessage(size_t count, bool& other_fr);

  std::wstring GetName() const { return user_name.data(); }
};