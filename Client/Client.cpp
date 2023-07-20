#include "Client.h"

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
  /* Проверка логина */
  net::message<msg_type> message;
  message.header.id = msg_type::CheckLogin;
  std::copy(&login[0], &login[0] + login.size(), &message.data[0]);
  send(message);
}

void Client::CheckPassword(const std::wstring& password) {
  /* Проверка пароля */
  net::message<msg_type> message;
  message.header.id = msg_type::CheckPassword;
  message.header.userid = userid_;
  std::copy(&password[0], &password[0] + password.size(), &message.data[0]);
  send(message);
}

void Client::SetUserid(uint32_t userid) {
  userid_ = userid;
}

void Client::CheckUpdateByIdChat(size_t id) {
  /* Проверка обновлений в чате.*/
  net::message<msg_type> message;
  message.header.id = msg_type::GetUpdateById;
  message.header.userid = userid_;
  std::copy(reinterpret_cast<const wchar_t*>(&id), reinterpret_cast<const wchar_t*>(&id) + sizeof(size_t), &message.data[0]);
  send(message);
}

std::vector<std::string> Client::GetFriend(size_t count) {
  net::message<msg_type> message;
  message.header.id = msg_type::GetImg;
  message.header.userid = userid_;
  send(message);
  return {{"Sofi"}, {"Tony"}
  };
}

std::vector<std::string> Client::GetMessage(size_t count) {
  return {};
}
