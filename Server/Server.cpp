
#include <fstream>
#include "Server.h"
#include <algorithm>

void Server::__on_message(std::shared_ptr<net::connection<msg_type>> connection_cl,
                            net::message<msg_type>& message) {
  switch (message.header.id) {
  case msg_type::CheckLogin: {
    CheckLogin(connection_cl, message);
    break;
  }

  case msg_type::CheckPassword: {
    CheckPassword(connection_cl, message);
    break;
  }

  case msg_type::GetChat: {
    GetChat(connection_cl, message);
    break;
  }

  case msg_type::StopServer: {
    server_do = false;
    break;
  }

  case msg_type::GetMessages: {
    GetMessages(connection_cl, message);
    break;
  }

  case msg_type::LastMessageId: {
    LastMessageId(connection_cl, message);
    break;
  }
  }
}

void Server::CheckLogin(std::shared_ptr<net::connection<msg_type>> connection_cl, net::message<msg_type>& message) {
  /* Если переданный от пользователя логин корректен, то возвращаем его id. */
  std::wcout << "CheckLogin: " << message.data.data() << std::endl;
  std::string login = message.data.data();
  int id;
  if ((id = db.GetIdByLogin(login)) != -1) {
    message.header.id = msg_type::LoginValid;
    std::copy(reinterpret_cast<char*>(&id), reinterpret_cast<char*>(&id) + 4, &message.data[0]);
  } else {
    message.header.id = msg_type::LoginInvalid;
  }
  connection_cl->send(message);
}

void Server::CheckPassword(std::shared_ptr<net::connection<msg_type>> connection_cl, net::message<msg_type>& message) {
  /* Проверка переданного id и пароля. */
  std::cout << "CheckPassword " << message.data.data() << std::endl;
  std::string password = message.data.data() + sizeof(int);
  int id;
  std::copy(&message.data[0], &message.data[0] + 4, reinterpret_cast<char*>(&id));
  if (db.CheckPassword(password, id)) {
    message.header.id = msg_type::PasswordValid;
  } else {
    message.header.id = msg_type::PasswordInvalid;
  }
  connection_cl->send(message);
}

void Server::GetChat(std::shared_ptr<net::connection<msg_type>> connection_cl, net::message<msg_type>& message) {
  /* Передача данных клиенту в случае запроса GetChat. */
  // msg input: data: [int id, int count]
  // msg output: data [char = 1, int id_chat, int size, std::string name_chat(name_chat.size() = size), char = 1 ..., char = 0]
  std::cout << "GetChat " << message.data.data() << std::endl;
  int id, count_before;
  std::copy(&message.data[0], &message.data[0] + 4, reinterpret_cast<char*>(&id));
  std::copy(&message.data[0] + 4, &message.data[0] + 8, reinterpret_cast<char*>(&count_before));
  pqxx::result chats = db.GetChat(id, count_before);

  size_t j = 0;
  bool send_more = true;
  net::message<msg_type> n_message;
  n_message.header.id = msg_type::SendImgMore;

  for (auto row = chats.begin(); row != chats.end(); ++row) {
    if (252 - j + 1 + 4 + 4  + row[1].as<std::string>().size()) {
      std::string name = row[1].as<std::string>();
      int id = row[0].as<int>();
      int size = name.size();

      n_message.data[j++] = 1;
      std::copy(reinterpret_cast<char*>(&id), reinterpret_cast<char*>(&id) + 4, &n_message.data[j]);
      std::copy(reinterpret_cast<char*>(&size), reinterpret_cast<char*>(&size) + 4, &n_message.data[j + 4]);
      std::copy(&name[0], &name[0] + size, &n_message.data[j + 8]);
      std::cout << id << " " << size << " " << name << std::endl;
      j += 8 + name.size();
      message.data[j] = 0;
      send_more = true;
    } else {
      connection_cl->send(n_message);
      j = 0;
      send_more = false;
    }
  }
  if (send_more) {
    connection_cl->send(n_message);
  }
  message.header.id = msg_type::SendImgFinish;
  connection_cl->send(message);
}

void Server::GetMessages(std::shared_ptr<net::connection<msg_type>> connection_cl, net::message<msg_type>& message) {
  std::cout << "GetMessages" << std::endl;
  int chatid, count_before;
  std::copy(&message.data[0], &message.data[0] + 4, reinterpret_cast<char*>(&chatid));
  std::copy(&message.data[0] + 4, &message.data[0] + 8, reinterpret_cast<char*>(&count_before));
  pqxx::result messages = db.GetMessages(chatid, count_before);

  size_t j = 0;
  net::message<msg_type> n_message;
  n_message.header.id = msg_type::SendMsgMore;
  bool send_more = true;

  for (auto row = messages.begin(); row != messages.end(); ++row) {
    std::string name = row[1].as<std::string>();
    int id = row[0].as<int>();
    int size = name.size();
    std::cout << id << " " << size << " " << name << std::endl;

    n_message.data[j++] = 1;
    std::copy(reinterpret_cast<char*>(&id), reinterpret_cast<char*>(&id) + 4, &n_message.data[j]);
    std::copy(reinterpret_cast<char*>(&size), reinterpret_cast<char*>(&size) + 4, &n_message.data[j + 4]);

    j += 8;
    int index_name = 0;

    while(size - index_name > 254 - j) {
      std::copy(&name[index_name], &name[index_name] + 254 - j, &n_message.data[j]);
      std::cout << id << " " << size << " " << name << std::endl;
      connection_cl->send(n_message);
      index_name += 254 - j;
      j = 0;
      std::cout << "NEW MESSAGE. \n (size - index_name) = " << size - index_name << std::endl;
    }

    if (size - index_name > 0) {
      send_more = true;
    } else {
      send_more = false;
    }
    //std::cout << id << " " << size << " " << name << std::endl;
    std::copy(&name[index_name], &name[index_name] + size - index_name, &n_message.data[j]);
    j += size - index_name;
    index_name = 0;
    n_message.data[j] = 0;
  }
  if (send_more) {
    connection_cl->send(n_message);
  }
  message.header.id = msg_type::SendMsgFinish;
  connection_cl->send(message);
}

void Server::LastMessageId(std::shared_ptr<net::connection<msg_type>> connection_cl, net::message<msg_type>& message) {
  
}