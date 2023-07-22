#include "Client.h"
#include "../include.h"
#include "fstream"

void Client::send_msg(std::string &__data) {
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

void Client::CheckLogin(const std::string& login) {
  /* Проверка логина */
  net::message<msg_type> message;
  message.header.id = msg_type::CheckLogin;
  std::copy(&login[0], &login[0] + login.size(), &message.data[0]);
  send(message);
}

void Client::CheckPassword(const std::string& password) {
  /* Проверка пароля */
  net::message<msg_type> message;
  message.header.id = msg_type::CheckPassword;
  std::copy(reinterpret_cast<const char*>(&userid_), reinterpret_cast<const char*>(&userid_) + 4, &message.data[0]);
  std::copy(&password[0], &password[0] + password.size(), &message.data[0] + 4);
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

std::vector<std::pair<int, std::string>> Client::GetChats() {
  // msg output:
  // data: [int id, int count]
  net::message<msg_type> message;
  message.header.id = msg_type::GetChat;
  std::copy(reinterpret_cast<char*>(&userid_), reinterpret_cast<char*>(&userid_) + 4, &message.data[0]);
  std::copy(reinterpret_cast<char*>(&count_chats_), reinterpret_cast<char*>(&count_chats_) + 4, &message.data[4]);
  send(message);
  count_chats_ += 20;

  std::this_thread::sleep_for(std::chrono::milliseconds(5)); // wait server
  bool more_message = true;
  std::vector<std::pair<int, std::string>> chats;

  while (more_message && is_connected() && !get_in_comming().empty()) {
    auto input_message = get_in_comming().pop_front().msg;
    int id, size;
    switch (input_message.header.id) {
      case msg_type::SendImgMore: {
        for (int i = 0; i < 256; ) {
          if (input_message.data[i++] == 0) {
            break;
          }
          // input_msg: 
          // data [char = 1, int id_chat, int size, std::string name_chat(name_chat.size() = size), char = 1 ..., char = 0]
          std::copy(&input_message.data[i], &input_message.data[i + 4], reinterpret_cast<char*>(&id));
          std::copy(&input_message.data[i + 4], &input_message.data[i + 8], reinterpret_cast<char*>(&size));
          std::string str(size, 'a');
          std::copy(&input_message.data[i + 8], &input_message.data[i + size + 8], &str[0]);
          i += 8 + size;
          chats.push_back({id, str});
        }
        break;
      }
      case msg_type::SendImgFinish: {
        more_message = false;
        break;
      }
    }
  }
  return chats;
}

std::vector<std::string> Client::GetMessage(size_t count) {
  net::message<msg_type> message;
  message.header.id = msg_type::GetMessages;
  std::copy(reinterpret_cast<char*>(&chatid_), reinterpret_cast<char*>(&chatid_) + 4, &message.data[0]);
  std::copy(reinterpret_cast<char*>(&message_index_), reinterpret_cast<char*>(&message_index_) + 4, &message.data[4]);
  send(message);

  std::this_thread::sleep_for(std::chrono::milliseconds(5)); // wait server
  int id, index_str = 0;
  bool more_message = true, next_message = false;
  std::vector<std::string> chats;
  std::string str;

   while (more_message && is_connected() && !get_in_comming().empty()) {
    auto input_message = get_in_comming().pop_front().msg;
    switch (input_message.header.id) {
      case msg_type::SendMsgMore: {
        std::cout << "NEW MESSAGE" << std::endl;
        for (int i = 0; i < 254; ) {
          std::cout << "Index i = " << i << std::endl;
          // input_msg: 
          // data [char = 1, int id_chat, int size,
          // std::string name_chat(name_chat.size() = size),
          // char = 1 ..., char = 0]
          if (!next_message) {
            std::cout << "Scanf id and size_msg" << std::endl;
            if (input_message.data[i++] == 0) {
              size_msg_last_ = 0;
              break;
            }
            std::copy(&input_message.data[i], &input_message.data[i] + 4, reinterpret_cast<char*>(&id));
            std::copy(&input_message.data[i] + 4, &input_message.data[i] + 8, reinterpret_cast<char*>(&size_msg_last_));
            std::cout << "id = " << id << " size = " << size_msg_last_ << std::endl;
            str.resize(size_msg_last_);
            i += 8;
          }
          if (size_msg_last_ < 254 - i) {
            std::cout << "Small size. size_msg_last_ = " << size_msg_last_ << std::endl;
            std::copy(&input_message.data[i], &input_message.data[i + size_msg_last_], &str[index_str]);
            index_str = 0;
            i += size_msg_last_;
            next_message = false;
            std::cout << str << std::endl;
            chats.push_back(str);
            size_msg_last_ = 0;
          } else {
            std::cout << "BIG SIZE. size_msg_last_ = " << size_msg_last_ << " i = " <<  i << std::endl;
            std::copy(&input_message.data[i], &input_message.data[254], &str[index_str]);
            index_str += 254 - i;
            next_message = true;
            size_msg_last_ -= 254 - i;
            i = 254;
          }
        }
        break;
      }
      case msg_type::SendImgFinish: {
        std::cout << "SendImgFinish\n";
        more_message = false;
        break;
      }
    }
  }
  return chats;
}
