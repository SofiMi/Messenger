
#include <fstream>
#include "Server.h"

bool Server::__on_client_connect(std::shared_ptr<net::connection<msg_type>> client) {
  return true;
}

void Server::__on_client_disconnect(std::shared_ptr<net::connection<msg_type>> client) {
  std::cout << "Removing client [" << client->get_id() << "] \n";
}

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

  case msg_type::StopServer: {
    server_do = false;
    break;
  }

  case msg_type::GetChat: {
    GetChat(connection_cl, message);
  }

  /*
  case msg_type::GetUpdateById: {
    int chat_id = 0;
    //__msg.header.id = msg_type::ServerMessage;
    //__msg.header.name = msg.header.name;
    std::copy(&msg.data[0], &msg.data[0] + sizeof(size_t),
              reinterpret_cast<char *>(&chat_id));
    std::cout << "User_id = " << msg.header.userid
              << ". Chat_id = " << chat_id << std::endl;
    net::message<msg_type> new_msg;
    new_msg.header.id = msg_type::NewMessageToThisChat;
    new_msg.header.userid = chat_id;
    std::string __data = "Hello!";
    for (unsigned int i = 0; i < __data.size(); ++i) {
      new_msg.data[i] = __data[i];
    }
    client->send(new_msg);
  }
  */

  /*
  case msg_type::GetImg : {
    SendImg(client);
  }
  */
  }
}

void Server::SendImg(std::shared_ptr<net::connection<msg_type>> client) {
  std::string name = "images.jpeg";
  std::ifstream in(name, std::ios::binary);
  std::ofstream out(std::string("clientImageSofi.jpeg"), std::ios::binary);

  if (!in.good()) {
    //throw;
    return;
  }

  in.seekg(0, std::ios::end);
  size_t myFileSize = in.tellg();
  in.seekg(0, std::ios::beg);

  std::cout << "Count msg: " << myFileSize / 256 << std::endl;

  while (in.tellg() < myFileSize) {
    net::message<msg_type> __msg;
    __msg.header.id = msg_type::SendImgMore;
    in.read((char*)__msg.data.data(), 256);
    out.write((char*)__msg.data.data(), 256);
    client->send(__msg);
    std::cout << "send" << std::endl;
  }
  std::cout << "END" << std::endl;
  net::message<msg_type> __msg;
  __msg.header.id = msg_type::SendImgFinish;
  client->send(__msg);
  in.close();
  out.close();
}

void Server::CheckLogin(std::shared_ptr<net::connection<msg_type>> connection_cl, net::message<msg_type>& message) {
  std::wcout << "CheckLogin " << message.data.data() << std::endl;
  std::string login = message.data.data();
  int id;
  if ((id = db.GetIdByLogin(login)) != -1) {
    message.header.id = msg_type::LoginValid;
    std::copy(reinterpret_cast<const char*>(&id), reinterpret_cast<const char*>(&id) + 4, &message.data[0]);
  } else {
    message.header.id = msg_type::LoginInvalid;
  }
  connection_cl->send(message);
}

void Server::CheckPassword(std::shared_ptr<net::connection<msg_type>> connection_cl, net::message<msg_type>& message) {
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