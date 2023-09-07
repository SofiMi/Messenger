#pragma once

#include "../include.h"
#include "../NetWork/net_message.h"
#include "../NetWork/net_queue.h"
#include "../NetWork/net_connection.h"

#include <string>
#include <iostream>
#include <vector>
#include <string>

#define ASIO_STANDALONE
#include <boost/asio.hpp>

class Client {
 public:
  ~Client();
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

  bool CheckChatName(const std::string& name, int& chatid);
  bool CheckTetAtTetChat(const std::string& nick, int& chatid, std::string& name);
  int CreateNewChat(const std::string& nick, std::string& namechat);

  std::vector<std::string> GetDataUpdate();

  int chatid_ = 0;
  int last_accept_message_id_in_chat_ = 20;

  bool is_connected();
  void send(const net::message<msg_type>& message);
  bool connect(const std::string& host, const uint16_t port);
  void disconnect();
 private:
  void CheckLogin(const std::string& login);
  void CheckPassword(const std::string& password);
  void RequestForMessages();
  void AcceptMessages(std::vector<std::string>& result, uint32_t enum_send_more, uint32_t finish);
  std::string GetName(int id);

  int userid_;
  int count_chats_ = 0;
  int size_msg_last_ = 0;
  int last_index_in_chat_ = 0;
  std::string name;

  static const int COUNT_OLD_MESSAGES = 20;
  static const int MESSAGE_BUFFER_SIZE = 254;

  boost::asio::io_context asio_context;
  std::thread thr;
  std::unique_ptr<net::connection<msg_type>> server_connection;
  net::ts_queue<net::owned_message<msg_type>> message_queue;

  net::ts_queue<net::owned_message<msg_type>>& get_in_comming();
};
