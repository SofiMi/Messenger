#pragma once
#include "net_client.h"
#include "../include.h"
#include <vector>
#include <string>

class Client : public net::client_interface<msg_type> {
 private:
  std::array<wchar_t, 256> user_name{};
  uint32_t userid_;
 public:
  void CheckLogin(const std::wstring& login);
  void CheckPassword(const std::wstring& password);

  void CheckUpdateByIdChat(size_t id);
  void send_msg(std::wstring& __data);
  void SetUserid(uint32_t userid);
  std::vector<std::tuple<int, std::string, std::vector<std::array<wchar_t, 256>>>> GetFriend(size_t count);
  std::vector<std::string> GetMessage(size_t count);

  std::wstring GetName() const { return user_name.data(); }
};
