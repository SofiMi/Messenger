#include "Client.h"

void Client::join_server() {
  std::cout << "Input Your Name: ";
  std::wcin.get(user_name.data(), user_name.size());
  std::wcin.clear();
  std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  net::message<msg_type> msg;
  msg.header.id = msg_type::JoinServer;
  msg.header.name = user_name;
  send(msg);
}

void Client::send_msg(std::wstring &__data) {
  net::message<msg_type> msg;
  msg.header.id = msg_type::PassString;
  msg.header.name = user_name;
  msg.header.userid = 4;

  for (unsigned int i = 0, j = 0; j < __data.size(); ++i, ++j) {
    msg.data[i] = __data[j];
    if (i == 255) {
      send(msg);
      i = 0;
    }
  }

  send(msg);
}

void Client::CheckLogin(const std::wstring& login) {
  net::message<msg_type> msg;
  msg.header.id = msg_type::CheckLogin;

  for (size_t i = 0; i < login.size(); ++i) {
    msg.data[i] = login[i];
  }
  send(msg);
}

void Client::CheckPassword(const std::wstring& password) {
  net::message<msg_type> msg;
  msg.header.id = msg_type::CheckPassword;
  msg.header.userid = userid;

  for (size_t i = 0; i < password.size(); ++i) {
    msg.data[i] = password[i];
  }
  send(msg);
}

void Client::StopServer() {
  net::message<msg_type> msg;
  msg.header.id = msg_type::StopServer;
  send(msg);
}