#pragma once
#include "net_client.h"
#include "../include.h"
#include <vector>
#include <string>

class Client : public net::client_interface<msg_type> {
 public:
  // Авторизация и рестрация
  bool Autorization(const std::string& login, const std::string& password, std::string& error_message);
  void AddNewUser(std::vector<std::string>& user_info);
  bool CheckUniqueNickname(const std::string& nickname);
  bool CheckUniqueLogin(const std::string& nickname);

  // Главная страница
  std::vector<std::pair<int, std::string>> GetChats();
  std::vector<std::string> GetMessage();
  void GetLastIdMessage();
  void SendNewMessage(const std::string& text);
  int chatid_ = 1;
  int last_accept_message_id_in_chat_ = 20;
 private:
  void CheckLogin(const std::string& login);
  void CheckPassword(const std::string& password);
  void RequestForMessages();
  void AcceptMessages(std::vector<std::string>& result);

  int userid_;
  int count_chats_ = 0;
  int size_msg_last_ = 0;

  static const int COUNT_OLD_MESSAGES = 20;
  static const int MESSAGE_BUFFER_SIZE = 254;
};
