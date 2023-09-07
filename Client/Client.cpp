#include "Client.h"
#include "../include.h"
#include "fstream"
#include <unordered_map>

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

  int i = 0;
  while(is_connected() && get_in_comming().empty()) {
    //std::cout << "wait chats\n";
    i++;
    if (i % 1000000 == 0) {
      //std::cout << "send message\n";
      send(message);
      std::this_thread::sleep_for(std::chrono::milliseconds(5)); // wait server
    }
  }

  while (more_message && is_connected()) {
    if (!get_in_comming().empty()) {
      auto input_message = get_in_comming().pop_front().msg;
      int id, size;
      switch (input_message.header.id) {
        case msg_type::NewMessage: {
          std::cout << "[-----------New message----------]" << std::endl;
          break;
        }
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
  }
  return chats;
}

std::vector<std::string> Client::GetMessage() {
  if (last_accept_message_id_in_chat_ <= 0) {
    return {};
  }
  RequestForMessages();
  std::vector<std::string> messages;
  AcceptMessages(messages, static_cast<uint32_t>(msg_type::SendMsgMore), static_cast<uint32_t>(msg_type::SendMsgFinish));
  return messages;
}

void Client::RequestForMessages() {
  /* 
    Отправляет запрос на сервер с новой порцией старых сообщений.
    Передаем id текущего чата и последнеe доставленное id сообщения в чате.
  */
  std::cout << "RequestForMessages()" << std::endl;
  //std::cout << "[Request] " << last_accept_message_id_in_chat_ << std::endl;
  net::message<msg_type> message;
  message.header.id = msg_type::GetMessages;
  std::copy(reinterpret_cast<char*>(&chatid_), reinterpret_cast<char*>(&chatid_) + 4, &message.data[0]);
  std::copy(reinterpret_cast<char*>(&last_accept_message_id_in_chat_), reinterpret_cast<char*>(&last_accept_message_id_in_chat_) + 4, &message.data[4]);
  send(message);
  last_accept_message_id_in_chat_ -= COUNT_OLD_MESSAGES;
  std::this_thread::sleep_for(std::chrono::milliseconds(5)); // wait server
}

void Client::AcceptMessages(std::vector<std::string>& result, uint32_t enum_send_more, uint32_t finish) {
  std::cout << "\n[Start AcceptMessages]" << std::endl;
  /*
    Принимаем сообщения 2 подтипов:
      - [char 0|1, int id_msg, int size, std::string, char 0|1 ...]
      - [std::string, char 0|1 ...]
    Второе сообщение отправляется в том случае, если принимаемый текст не поместился
    в предыдущее и является его продолжением.
  */
  std::string input_text;
  int id_msg, index_in_input_text = 0;
  bool will_be_more_messages = true, is_next_message = false;

  bool need_read_check = true;
  bool need_read_id = true;
  bool need_read_size = true;

  std::vector<int> userids;
  std::unordered_map<int, std::string> name_by_id;
  
  while (is_connected() && get_in_comming().empty()) {
    //std::cout << "wait messages\n" << std::endl;
  }

  while (will_be_more_messages && is_connected()) {
    if (!get_in_comming().empty()) {
      auto input_message = get_in_comming().pop_front().msg;
      //std::cout << "I have msg by server. Index of msg.id = " << static_cast<uint>(input_message.header.id) << std::endl;
      if (static_cast<uint32_t>(input_message.header.id) == enum_send_more) {
          //std::cout << "Accept MSS" << std::endl;
          for (int index_in_message = 0; index_in_message < MESSAGE_BUFFER_SIZE; ) {
            if (need_read_check) {
              if (input_message.data[index_in_message++] == 0) {
                break;
              }
            }

            if (need_read_id) {
              if (MESSAGE_BUFFER_SIZE - index_in_message < 4) {
                need_read_check = false;
                need_read_id = true;
                need_read_size = true;
                break;
              }
              std::copy(&input_message.data[index_in_message], &input_message.data[index_in_message] + 4, reinterpret_cast<char*>(&id_msg));
              index_in_message += 4;
            }

            if (need_read_size) {
              if (MESSAGE_BUFFER_SIZE - index_in_message < 4) {
                need_read_check = false;
                need_read_id = false;
                need_read_size = true;
                break;
              }
              std::copy(&input_message.data[index_in_message], &input_message.data[index_in_message] + 4, reinterpret_cast<char*>(&size_msg_last_));
              input_text.resize(size_msg_last_);
              index_in_message += 4;
            }

            if (size_msg_last_ <= MESSAGE_BUFFER_SIZE - index_in_message) {
              // принимаемый текст помещается в текущее сообщение
              std::copy(&input_message.data[index_in_message], &input_message.data[index_in_message + size_msg_last_], &input_text[index_in_input_text]);
              result.push_back(input_text);
              userids.push_back(id_msg);
              //std::cout << "[AC]: " << input_text << std::endl;

              index_in_message += size_msg_last_;
              size_msg_last_ = 0;
              index_in_input_text = 0;

              need_read_check = true;
              need_read_id = true;
              need_read_size = true;
            } else {
              // принимаемый текст не помещается в текущее сообщение
              std::copy(&input_message.data[index_in_message], &input_message.data[MESSAGE_BUFFER_SIZE], &input_text[index_in_input_text]);

              size_msg_last_ -= MESSAGE_BUFFER_SIZE - index_in_message;
              index_in_input_text += MESSAGE_BUFFER_SIZE - index_in_message;
              index_in_message = MESSAGE_BUFFER_SIZE;

              need_read_check = false;
              need_read_id = false;
              need_read_size = false;
            }
          }
        } else if (static_cast<uint32_t>(input_message.header.id) == finish) {
          //std::cout << "Finish" << std::endl;
          will_be_more_messages = false;
        } 
    }
  }
  //std::cout << "[End AcceptMessages]\n" << std::endl;

  for (int i = 0; i < result.size(); ++i) {
    if (name_by_id.find(userids[i]) == name_by_id.end()) {
      name_by_id[userids[i]] = GetName(userids[i]);
    }
    result[i] = std::string("<b>") + name_by_id[userids[i]] + "</b> <br>" + result[i];
  }
}

bool Client::Autorization(const std::string& login, const std::string& password, std::string& error_message) {
  CheckLogin(login);
  std::this_thread::sleep_for(std::chrono::milliseconds(5)); // wait server
  
  while(is_connected() && get_in_comming().empty()) {
    //std::cout << "wait autorization\n";
  }

  if (is_connected() && !get_in_comming().empty()) {
    auto message_login = get_in_comming().pop_front().msg;

    switch (message_login.header.id) {
      case msg_type::LoginValid: {
        std::copy(&message_login.data[0], &message_login.data[4], reinterpret_cast<char*>(&userid_));
        CheckPassword(password);
        std::this_thread::sleep_for(std::chrono::milliseconds(5)); // wait server

        if (is_connected() && !get_in_comming().empty()) {
          auto message_password = get_in_comming().pop_front().msg;

          switch (message_password.header.id) {
            case msg_type::PasswordValid: {
              return true;
            }
            case msg_type::PasswordInvalid: {
              error_message = "Неверный пароль.\n";
              return false;
            }
            default: {
              error_message = "Ошибка сервера во время загрузки пароля.\n";
              return false;
            }
          }
        } else {
          error_message = "Не пришло сообщение от сервера во время загрузки пароля.\n";
          return false;
        }
      }
      case msg_type::LoginInvalid: {
        error_message = "Неверный логин.\n";
        return false;
      }
      default: {
        error_message = "Ошибка сервера.\n";
        return false;
      }
    }
  } else {
    error_message = "Не пришло сообщение от сервера";
    return false;
  }
}

void Client::GetLastIdMessage() {
  /* Устанавливаем id последнего сообщения в текущем чате. */
  net::message<msg_type> message;
  message.header.id = msg_type::LastMessageId;
  std::copy(reinterpret_cast<char*>(&chatid_), reinterpret_cast<char*>(&chatid_) + 4, &message.data[0]);
  std::copy(reinterpret_cast<char*>(&userid_), reinterpret_cast<char*>(&userid_) + 4, &message.data[4]);
  send(message);
  std::this_thread::sleep_for(std::chrono::milliseconds(5)); // wait server

  while (is_connected() && get_in_comming().empty()) {}

  if (is_connected() && !get_in_comming().empty()) {
    auto message_result = get_in_comming().pop_front().msg;
    switch (message_result.header.id) {
      case msg_type::NewMessage: {
        std::cout << "[-----------New message----------]" << std::endl;
        break;
      }
      case msg_type::LastMessageId: {
        std::copy(&message_result.data[0], &message_result.data[0] + 4, reinterpret_cast<char*>(&last_accept_message_id_in_chat_));
        last_index_in_chat_ = last_accept_message_id_in_chat_ - 1;
        break;
      }
    }
  }
}

void Client::SendNewMessage(const std::string& text) {
  //std::cout << "chatid " << chatid_ << std::endl;
  int size_text = text.size();
  //std::cout << size_text << std::endl;
  net::message<msg_type> message;
  message.header.id = msg_type::NewMessage;

  std::copy(reinterpret_cast<char*>(&userid_), reinterpret_cast<char*>(&userid_) + 4, &message.data[0]);
  std::copy(reinterpret_cast<char*>(&chatid_), reinterpret_cast<char*>(&chatid_) + 4, &message.data[4]);
  std::copy(reinterpret_cast<char*>(&size_text), reinterpret_cast<char*>(&size_text) + 4, &message.data[8]);

  int index_text = 0;

  if (size_text <= MESSAGE_BUFFER_SIZE - 12) {
    std::copy(&text[index_text], &text[index_text] + size_text, &message.data[12]);
    send(message);
  } else {
    std::copy(&text[index_text], &text[index_text] + MESSAGE_BUFFER_SIZE - 12, &message.data[12]);
    size_text -= MESSAGE_BUFFER_SIZE - 12;
    index_text += MESSAGE_BUFFER_SIZE - 12;
    send(message);

    while (size_text > MESSAGE_BUFFER_SIZE - 4) {
      std::copy(reinterpret_cast<char*>(&userid_), reinterpret_cast<char*>(&userid_) + 4, &message.data[0]);
      std::copy(&text[index_text], &text[index_text] + MESSAGE_BUFFER_SIZE - 4, &message.data[4]);
      size_text -= MESSAGE_BUFFER_SIZE - 4;
      index_text += MESSAGE_BUFFER_SIZE - 4;
      send(message);
    }

    if (size_text > 0) {
      std::copy(reinterpret_cast<char*>(&userid_), reinterpret_cast<char*>(&userid_) + 4, &message.data[0]);
      std::copy(&text[index_text], &text[index_text] + size_text, &message.data[4]);
      send(message);
    }
  }
}

void Client::AddNewUser(std::vector<std::string>& user_info) {
  /*  Регистрация нового пользователя.

      std::vector<std::string> user_info = {
        login,
        password,
        name,
        nickname
      }
  */
  net::message<msg_type> message;
  message.header.id = msg_type::AddNewUser;
  int index_msg = 0;

  for (int i = 0; i < 4; ++i) {
    int size_text = user_info[i].size();
    std::copy(reinterpret_cast<char*>(&size_text), reinterpret_cast<char*>(&size_text) + 4, &message.data[index_msg]);
    std::copy(reinterpret_cast<char*>(&user_info[i][0]), reinterpret_cast<char*>(&user_info[i][0]) + size_text, &message.data[index_msg + 4]);
    index_msg += 4 + size_text;
  }

  send(message);

  while (is_connected() && get_in_comming().empty()) {}

  if (is_connected() && get_in_comming().empty()) {
    auto message_result = get_in_comming().pop_front().msg;
    switch (message_result.header.id) {
      case msg_type::AddNewUser: {
        std::copy(&message.data[0], &message.data[0] + 4, &userid_);
        break;
      }
    }
  }
}

bool Client::CheckUniqueNickname(const std::string& nickname) {
  /* Проверка того, является ли никнейм уникальным. */
  net::message<msg_type> message;
  message.header.id = msg_type::CheckUniqueNick;
  int size = nickname.size();
  std::copy(reinterpret_cast<char*>(&size), reinterpret_cast<char*>(&size) + 4, &message.data[0]);
  std::copy(reinterpret_cast<const char*>(&nickname[0]), reinterpret_cast<const char*>(&nickname[0]) + size, &message.data[4]);
  send(message);

  while (is_connected() && get_in_comming().empty()) {}

  if (is_connected() && !get_in_comming().empty()) {
    auto message_result = get_in_comming().pop_front().msg;
    switch (message_result.header.id) {
      case msg_type::CheckUniqueNick: {
        std::copy(&message_result.data[0], &message_result.data[0] + 4, reinterpret_cast<char*>(&size));
        break;
      }
    }
  }
  return size == 0;
}

bool Client::CheckUniqueLogin(const std::string& login) {
  /* Проверка того, является ли логин уникальным. */
  net::message<msg_type> message;
  message.header.id = msg_type::CheckUniqueLogin;
  int size = login.size();
  std::copy(reinterpret_cast<char*>(&size), reinterpret_cast<char*>(&size) + 4, &message.data[0]);
  std::copy(reinterpret_cast<const char*>(&login[0]), reinterpret_cast<const char*>(&login[0]) + size, &message.data[4]);
  send(message);

  while (is_connected() && get_in_comming().empty()) {}

  if (is_connected() && !get_in_comming().empty()) {
    auto message_result = get_in_comming().pop_front().msg;
    switch (message_result.header.id) {
      case msg_type::CheckUniqueLogin: {
        std::copy(&message_result.data[0], &message_result.data[0] + 4, reinterpret_cast<char*>(&size));
        break;
      }
    }
  }
  return size == 0;
}

bool Client::CheckChatName(const std::string& name, int& chatid) {
  int size_name = name.size();
  net::message<msg_type> output_message;
  output_message.header.id = msg_type::CheckChatName;
  std::copy(reinterpret_cast<char*>(&userid_),reinterpret_cast<char*>(&userid_) + 4, &output_message.data[0]);
  std::copy(reinterpret_cast<char*>(&size_name),reinterpret_cast<char*>(&size_name) + 4, &output_message.data[4]);
  std::copy(&name[0], &name[size_name], &output_message.data[8]);
  send(output_message);

  while (is_connected() && get_in_comming().empty()) {}

  if (is_connected() && !get_in_comming().empty()) {
    auto input_message = get_in_comming().pop_front().msg;
    switch (input_message.header.id) {
      case msg_type::CheckChatName: {
        std::copy(&input_message.data[0], &input_message.data[4], reinterpret_cast<char*>(&chatid));
        break;
      }
    }
  }

  return chatid != 0;
}

bool Client::CheckTetAtTetChat(const std::string& nick, int& chatid, std::string& name) {
  int size_name = nick.size();
  net::message<msg_type> output_message;
  output_message.header.id = msg_type::CheckTetAtTetChat;
  std::copy(reinterpret_cast<char*>(&userid_),reinterpret_cast<char*>(&userid_) + 4, &output_message.data[0]);
  std::copy(reinterpret_cast<char*>(&size_name),reinterpret_cast<char*>(&size_name) + 4, &output_message.data[4]);
  std::copy(&nick[0], &nick[size_name], &output_message.data[8]);
  send(output_message);

  while (is_connected() && get_in_comming().empty()) {}

  if (is_connected() && !get_in_comming().empty()) {
    auto input_message = get_in_comming().pop_front().msg;
    switch (input_message.header.id) {
      case msg_type::CheckTetAtTetChat: {
        std::copy(&input_message.data[0], &input_message.data[4], reinterpret_cast<char*>(&chatid));
        std::copy(&input_message.data[4], &input_message.data[8], reinterpret_cast<char*>(&size_name));
        std::copy(&input_message.data[8], &input_message.data[8 + size_name], reinterpret_cast<char*>(&name[0]));
        break;
      }
    }
  }

  return chatid != 0;
}

int Client::CreateNewChat(const std::string& name, std::string& namechat) {
  int size_name = name.size(), chatid;
  net::message<msg_type> output_message;
  output_message.header.id = msg_type::CreateNewChat;
  std::copy(reinterpret_cast<char*>(&userid_),reinterpret_cast<char*>(&userid_) + 4, &output_message.data[0]);
  std::copy(reinterpret_cast<char*>(&size_name),reinterpret_cast<char*>(&size_name) + 4, &output_message.data[4]);
  std::copy(&name[0], &name[size_name], &output_message.data[8]);
  send(output_message);

  while (is_connected() && get_in_comming().empty()) {}

  if (is_connected() && !get_in_comming().empty()) {
    auto input_message = get_in_comming().pop_front().msg;
    switch (input_message.header.id) {
      case msg_type::CreateNewChat: {
        std::copy(&input_message.data[0], &input_message.data[4], reinterpret_cast<char*>(&chatid));
        std::copy(&input_message.data[4], &input_message.data[8], reinterpret_cast<char*>(&size_name));
        std::copy(&input_message.data[8], &input_message.data[8 + size_name], reinterpret_cast<char*>(&namechat[0]));
        break;
      }
    }
  }

  return chatid;
}


std::vector<std::string> Client::GetDataUpdate() {
  int last_msg_id;
  net::message<msg_type> output_message;

  output_message.header.id = msg_type::GetLastMsgId;
  std::copy(reinterpret_cast<char*>(&chatid_),reinterpret_cast<char*>(&chatid_) + 4, &output_message.data[0]);
  send(output_message);
  while (is_connected() && get_in_comming().empty()) {
  }
  if (is_connected() && !get_in_comming().empty()) {
    auto input_message = get_in_comming().pop_front().msg;
    switch (input_message.header.id) {
      case msg_type::GetLastMsgId: {
        //std::cout << "GetLastMsgId" << std::endl;
        std::copy(&input_message.data[0], &input_message.data[4], reinterpret_cast<char*>(&last_msg_id));
        break;
      }
      default: {
        //std::cout << "Id = " << static_cast<uint32_t>(input_message.header.id) << std::endl;
      }
    }
  }

  //std::cout << "last_msg_id = " << last_msg_id << ". last_index_in_chat_  = " << last_index_in_chat_ << std::endl; 

  if (last_msg_id == last_index_in_chat_) {
    return {};
  }

  output_message.header.id = msg_type::GetDataUpdate;
  //std::cout << "userid = " << userid_ << " chatid = " << chatid_ << "last_accept_message_id_in_chat_ = " << last_accept_message_id_in_chat_ << std::endl;
  int l = 5;
  std::copy(reinterpret_cast<char*>(&userid_),reinterpret_cast<char*>(&userid_) + 4, &output_message.data[0]);
  std::copy(reinterpret_cast<char*>(&chatid_),reinterpret_cast<char*>(&chatid_) + 4, &output_message.data[4]);
  std::copy(reinterpret_cast<char*>(&last_index_in_chat_),reinterpret_cast<char*>(&last_index_in_chat_) + 4, &output_message.data[8]);
  send(output_message);

  while (is_connected() && get_in_comming().empty()) {}

  std::vector<std::string> messages;
  AcceptMessages(messages, static_cast<uint32_t>(msg_type::SendUnpdateMore), static_cast<uint32_t>(msg_type::SendUnpdateFinish));
  last_index_in_chat_ = last_msg_id;
  return messages;
}

Client::~Client() { disconnect(); }

bool Client::connect(const std::string& host, const uint16_t port) {
  try {
    boost::asio::ip::tcp::resolver resolver(asio_context);
    boost::asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(host, std::to_string(port));

    server_connection = std::make_unique<net::connection<msg_type>>(net::connection<msg_type>::owner::client, asio_context,
                                                                    boost::asio::ip::tcp::socket(asio_context), message_queue);
    server_connection->connect_to_server(endpoints);

    thr = std::thread([this]() { asio_context.run(); });
  } catch (std::exception &ex) {
    std::cerr << "Client Exception: " << ex.what() << '\n';
    return false;
  }
  return true;
}

void Client::disconnect() {
  if (is_connected()) {
    server_connection->disconnect();
  }

  asio_context.stop();
  if (thr.joinable())
    thr.join();

  server_connection.release();
}

bool Client::is_connected() {
  return server_connection ? server_connection->is_connected() : false;
}

void Client::send(const net::message<msg_type>& message) {
  if (is_connected()) {
    server_connection->send(message);
  }
}

net::ts_queue<net::owned_message<msg_type>>& Client::get_in_comming() { return message_queue; }

std::string Client::GetName(int id) {
  std::cout << "GetName" << std::endl;
  net::message<msg_type> message;
  message.header.id = msg_type::GetName;
  std::copy(reinterpret_cast<char*>(&id), reinterpret_cast<char*>(&id) + 4, &message.data[0]);
  send(message);

  while (is_connected() && get_in_comming().empty()) {}

  int size;
  std::string name;
  if (is_connected() && !get_in_comming().empty()) {
    auto input_message = get_in_comming().pop_front().msg;
    switch (input_message.header.id) {
      case msg_type::GetName: {
        std::copy(&input_message.data[0], &input_message.data[4], reinterpret_cast<char*>(&size));
        name.resize(size);
        std::copy(&input_message.data[4], &input_message.data[4 + size], &name[0]);
        break;
      }
    }
  }
  return name;
}