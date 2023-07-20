#include "Client.h"
#include "../include.h"
#include "fstream"

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

std::vector<std::tuple<int, std::string, std::vector<std::array<wchar_t, 256>>>> Client::GetFriend(size_t count) {
  std::vector<std::tuple<int, std::string, std::vector<std::array<wchar_t, 256>>>> result;

  net::message<msg_type> message;
  message.header.id = msg_type::GetImg;
  message.header.userid = userid_;
  send(message);

  std::this_thread::sleep_for(std::chrono::milliseconds(5)); // wait server
  bool more_message = true;

  std::vector<std::array<wchar_t, 256>> img;
  std::ofstream out(std::string("clientImageSofi.jpeg"), std::ios::binary);

  while (more_message && is_connected() && !get_in_comming().empty()) {
    auto msg = get_in_comming().pop_front().msg;

    switch (msg.header.id) {
      case msg_type::SendImgMore: {
        //img.push_back(msg.data);
        out.write((char*)msg.data.data(), 256);
        break;
      }
      case msg_type::SendImgFinish: {
        more_message = false;
        break;
      }
    }
  }
  result.push_back(std::tuple<int, std::string, std::vector<std::array<wchar_t, 256>>>(1, "Sofi", img));
  //out.close();
  return result;
}

std::vector<std::string> Client::GetMessage(size_t count) {
  return {};
}
