#pragma once
#include "net_client.h"
#include "../include.h"

class Client : public net::client_interface<msg_type> {
 private:
  std::array<wchar_t, 256> user_name{};
  size_t userid;
  bool GetNamebyServer();
 public:
  void join_server();
  void CheckLogin(const std::wstring& login);
  void CheckPassword(const std::wstring& password);
  void StopServer();
  void send_msg(std::wstring& __data);

  std::wstring GetName() const { return user_name.data(); }
};