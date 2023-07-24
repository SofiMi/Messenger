
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

    case msg_type::NewMessage: {
      NewMessage(connection_cl, message);
      break;
    }

    case msg_type::AddNewUser: {
      AddNewUser(connection_cl, message);
      break;
    }
    
    case msg_type::CheckUniqueLogin: {
      CheckUniqueLogin(connection_cl, message);
      break;
    }

    case msg_type::CheckUniqueNick: {
      CheckUniqueNick(connection_cl, message);
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
  std::cout << "\n[Start GetMessages]" << std::endl;
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
    std::cout << "[db res] id = " << id << " size = " << size << " name = " << name << std::endl;

    n_message.data[j++] = 1;
    std::copy(reinterpret_cast<char*>(&id), reinterpret_cast<char*>(&id) + 4, &n_message.data[j]);
    std::copy(reinterpret_cast<char*>(&size), reinterpret_cast<char*>(&size) + 4, &n_message.data[j + 4]);

    j += 8;
    int index_name = 0;

    while(size - index_name > 254 - j) {
      std::copy(&name[index_name], &name[index_name] + 254 - j, &n_message.data[j]);
      connection_cl->send(n_message);
      index_name += 254 - j;
      j = 0;
      std::cout << "Big msg. Send in the new msg. \n" << std::endl;
    }

    if (size - index_name > 0 || size == 0) {
      send_more = true;
    } else {
      send_more = false;
    }
    std::copy(&name[index_name], &name[index_name] + size - index_name, &n_message.data[j]);
    j += size - index_name;
    index_name = 0;
    n_message.data[j] = 0;
  }

  if (send_more) {
    connection_cl->send(n_message);
    std::cout << "Send msg." << std::endl;
  }

  message.header.id = msg_type::SendMsgFinish;
  connection_cl->send(message);
  std::cout << "\n[End GetMessages]" << std::endl;
}

void Server::LastMessageId(std::shared_ptr<net::connection<msg_type>> connection_cl, net::message<msg_type>& message) {
  // [chatid int, userid int]
  int userid, chatid;
  std::copy(reinterpret_cast<char*>(&message.data[0]), reinterpret_cast<char*>(&message.data[0]) + 4, reinterpret_cast<char*>(&chatid));
  std::copy(reinterpret_cast<char*>(&message.data[4]), reinterpret_cast<char*>(&message.data[4]) + 4, reinterpret_cast<char*>(&userid));

  int index = db.GetCountMsgInChat(chatid);
  std::copy(reinterpret_cast<char*>(&index), reinterpret_cast<char*>(&index) + 4, reinterpret_cast<char*>(&message.data[0]));
  connection_cl->send(message);
}

void Server::NewMessage(std::shared_ptr<net::connection<msg_type>> connection_cl, net::message<msg_type>& message) {
  std::cout << "NewMessage" << std::endl;
  int userid, chatid, size_text;
  bool is_new_message = false;
  std::copy(&message.data[0], &message.data[0] + 4, &userid);

  if (user_messages_memory_.find(userid) == user_messages_memory_.end() || (size_text = std::get<1>(user_messages_memory_[userid])) == 0) {
    user_messages_memory_[userid] = {};
    std::copy(&message.data[4], &message.data[8], &chatid);
    std::copy(&message.data[8], &message.data[12], &size_text);
    std::get<0>(user_messages_memory_[userid]) = chatid;
    std::get<1>(user_messages_memory_[userid]) = size_text;
    std::get<2>(user_messages_memory_[userid]) = std::string(size_text, 'a');
    std::get<3>(user_messages_memory_[userid]) = connection_cl;
    is_new_message = true;
  }

  if (std::get<3>(user_messages_memory_[userid]) != connection_cl) {
    std::get<3>(user_messages_memory_[userid]) = connection_cl;
  }

  std::string& str = std::get<2>(user_messages_memory_[userid]);
  int index = is_new_message ? 12 : 4;
  if (size_text <= 254 - index) {
    std::copy(&message.data[index], &message.data[index] + size_text, &str[str.size() - size_text]);
    std::get<1>(user_messages_memory_[userid]) = 0;
    db.InsertMsg(std::get<0>(user_messages_memory_[userid]), userid, str);
    std::cout << std::get<0>(user_messages_memory_[userid]) << " " << userid << " " <<  str << std::endl;

    pqxx::result res_userid = db.GetUseridByChatitd(std::get<0>(user_messages_memory_[userid]));
    net::message<msg_type> output_message;
    output_message.header.id = msg_type::NewMessage;
    for (auto iter: res_userid) {
      if (iter[0].as<int>() != userid && user_messages_memory_.find(iter[0].as<int>()) != user_messages_memory_.end()) {
        std::get<3>(user_messages_memory_[iter[0].as<int>()])->send(output_message);
      }
    }
  } else {
    std::copy(&message.data[index], &message.data[index] + 254 - index, &str[str.size() - size_text]);
    std::get<1>(user_messages_memory_[userid]) -= 254 - index;
  }
}

void Server::AddNewUser(std::shared_ptr<net::connection<msg_type>> connection_cl, net::message<msg_type>& message) {
  /*  Регистрация нового пользователя.

      std::vector<std::string> user_info = {
        login,
        password,
        name,
        nickname
      }
  */
  std::cout << "AddNewUser" << std::endl;
  int size_text, index_msg = 0;
  std::vector<std::string> user_info(4);

  for (int i = 0; i < 4; ++i) {
    std::copy(&message.data[index_msg], &message.data[index_msg + 4], reinterpret_cast<char*>(&size_text));
    user_info[i].resize(size_text);
    std::copy(&message.data[index_msg + 4], &message.data[index_msg + 4 + size_text], reinterpret_cast<char*>(&(user_info[i][0])));
    index_msg += 4 + size_text;
  }

  int userid = db.AddNewUser(user_info);
  std::copy(reinterpret_cast<char*>(&userid), reinterpret_cast<char*>(&userid) + 4, &message.data[0]);
  connection_cl->send(message);
}

void Server::CheckUniqueNick(std::shared_ptr<net::connection<msg_type>> connection_cl, net::message<msg_type>& message) {
  /* 
    Проверка уникальности никнейма.
    Если это правда, то будет отправлен 0.
  */
  int size_text;
  std::string nick;
  std::copy(&message.data[0], &message.data[4], reinterpret_cast<char*>(&size_text));
  nick.resize(size_text);
  std::copy(&message.data[4], &message.data[4 + size_text], reinterpret_cast<char*>(&nick[0]));

  int count_same_nick = db.CountSameNick(nick);
  std::copy(reinterpret_cast<char*>(&count_same_nick), reinterpret_cast<char*>(&count_same_nick) + 4, &message.data[0]);
  connection_cl->send(message);
}

void Server::CheckUniqueLogin(std::shared_ptr<net::connection<msg_type>> connection_cl, net::message<msg_type>& message) {
  /* 
    Проверка уникальности логина.
    Если это правда, то будет отправлен 0.
  */
  int size_text;
  std::string login;
  std::copy(&message.data[0], &message.data[4], reinterpret_cast<char*>(&size_text));
  login.resize(size_text);
  std::copy(&message.data[4], &message.data[4 + size_text], reinterpret_cast<char*>(&login[0]));

  int count_same_login = db.CountSameLogin(login);
  std::cout <<  count_same_login << std::endl;
  std::copy(reinterpret_cast<char*>(&count_same_login), reinterpret_cast<char*>(&count_same_login) + 4, &message.data[0]);
  connection_cl->send(message);
}