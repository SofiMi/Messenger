
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

    case msg_type::CheckChatName: {
      CheckChatName(connection_cl, message);
      break;
    }

    case msg_type::CreateNewChat: {
      CreateNewChat(connection_cl, message);
      break;
    }

    case msg_type::CheckTetAtTetChat: {
      CheckTetAtTetChat(connection_cl, message);
      break;
    }

    case msg_type::GetDataUpdate: {
      GetDataUpdate(connection_cl, message);
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

void Server::GetMessages(std::shared_ptr<net::connection<msg_type>> connection_cl, net::message<msg_type>& input_message) {
  std::cout << "\n[Start GetMessages]" << std::endl;
  int chatid, count_before;
  std::copy(&input_message.data[0], &input_message.data[0] + 4, reinterpret_cast<char*>(&chatid));
  std::copy(&input_message.data[0] + 4, &input_message.data[0] + 8, reinterpret_cast<char*>(&count_before));
  pqxx::result texts = db.GetMessages(chatid, count_before);
  SendManyMsg(connection_cl, static_cast<uint32_t>(msg_type::SendMsgMore), static_cast<uint32_t>(msg_type::SendMsgFinish), texts);
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
  std::copy(reinterpret_cast<char*>(&count_same_login), reinterpret_cast<char*>(&count_same_login) + 4, &message.data[0]);
  connection_cl->send(message);
}

void Server::CheckChatName(std::shared_ptr<net::connection<msg_type>> connection_cl, net::message<msg_type>& message) {
  int size_text, userid;
  std::string name;
  std::copy(&message.data[0], &message.data[4], reinterpret_cast<char*>(&userid));
  std::copy(&message.data[4], &message.data[8], reinterpret_cast<char*>(&size_text));
  name.resize(size_text);
  std::copy(&message.data[8], &message.data[8 + size_text], reinterpret_cast<char*>(&name[0]));

  int chatid = db.ChatIdByNameAndUserid(userid, name);
  std::copy(reinterpret_cast<char*>(&chatid), reinterpret_cast<char*>(&chatid) + 4, &message.data[0]);
  connection_cl->send(message);
}

void Server::CreateNewChat(std::shared_ptr<net::connection<msg_type>> connection_cl, net::message<msg_type>& message) {
  int size_text, userid;
  std::string name;
  std::copy(&message.data[0], &message.data[4], reinterpret_cast<char*>(&userid));
  std::copy(&message.data[4], &message.data[8], reinterpret_cast<char*>(&size_text));
  name.resize(size_text);
  std::copy(&message.data[8], &message.data[8 + size_text], reinterpret_cast<char*>(&name[0]));

  auto chat = db.CreateNewChat(userid, name);
  size_text = chat.second.size();
  std::copy(reinterpret_cast<char*>(&chat.first), reinterpret_cast<char*>(&chat.first) + 4, &message.data[0]);
  std::copy(reinterpret_cast<char*>(&size_text), reinterpret_cast<char*>(&size_text) + 4, &message.data[4]);
  std::copy(&chat.second[0], &chat.second[size_text], reinterpret_cast<char*>(&message.data[8]));
  connection_cl->send(message);
}

void Server::CheckTetAtTetChat(std::shared_ptr<net::connection<msg_type>> connection_cl, net::message<msg_type>& message) {
  int size_text, userid;
  std::string name;
  std::copy(&message.data[0], &message.data[4], reinterpret_cast<char*>(&userid));
  std::copy(&message.data[4], &message.data[8], reinterpret_cast<char*>(&size_text));
  name.resize(size_text);
  std::copy(&message.data[8], &message.data[8 + size_text], reinterpret_cast<char*>(&name[0]));

  int chatid = db.CheckTetAtTetChat(userid, name);
  std::copy(reinterpret_cast<char*>(&chatid), reinterpret_cast<char*>(&chatid) + 4, &message.data[0]);
  connection_cl->send(message);
}

void Server::SendManyMsg(std::shared_ptr<net::connection<msg_type>> connection_cl, uint32_t enum_send_more, uint32_t finish, pqxx::result& texts) {
  int index_message = 0;
  int index_name = 0;
  net::message<msg_type> output_message;
  output_message.header.id = static_cast<msg_type>(enum_send_more);
  bool send_more = true;

  for (auto row = texts.begin(); row != texts.end(); ++row) {
    std::string name = row[1].as<std::string>();
    int id = row[0].as<int>();
    int size_text = name.size();
    std::cout << "[db res] id = " << id << " size = " << size_text << " name = " << name << "index in msg = " << index_message << std::endl;

    output_message.data[index_message++] = 1;

    if (MESSAGE_BUFFER_SIZE - index_message < 4) {
      connection_cl->send(output_message);
      index_message = 0;
    }

    std::copy(reinterpret_cast<char*>(&id), reinterpret_cast<char*>(&id) + 4, &output_message.data[index_message]);
    index_message += 4;

    if (MESSAGE_BUFFER_SIZE - index_message < 4) {
      connection_cl->send(output_message);
      index_message = 0;
    }

    std::copy(reinterpret_cast<char*>(&size_text), reinterpret_cast<char*>(&size_text) + 4, &output_message.data[index_message]);
    index_message += 4;

    index_name = 0;
    while(size_text - index_name >= MESSAGE_BUFFER_SIZE - index_message) {
      std::copy(&name[index_name], &name[index_name] + MESSAGE_BUFFER_SIZE - index_message, &output_message.data[index_message]);
      connection_cl->send(output_message);
      index_name += MESSAGE_BUFFER_SIZE - index_message;
      index_message = 0;
      std::cout << "Big msg. Send in the new msg. \n" << std::endl;
    }

    std::copy(&name[index_name], &name[size_text], &output_message.data[index_message]);
    index_message += size_text - index_name;
    output_message.data[index_message] = 0;
  }
  
  connection_cl->send(output_message);

  output_message.header.id = static_cast<msg_type>(finish);
  connection_cl->send(output_message);
}

void Server::GetDataUpdate(std::shared_ptr<net::connection<msg_type>> connection_cl, net::message<msg_type>& input_message) {
  int userid, chatid, last_index_in_chat;
  std::copy(&input_message.data[0], &input_message.data[4], reinterpret_cast<char*>(&userid));
  std::copy(&input_message.data[4], &input_message.data[8], reinterpret_cast<char*>(&chatid));
  std::copy(&input_message.data[8], &input_message.data[12], reinterpret_cast<char*>(&last_index_in_chat));

  pqxx::result texts = db.GetDataUpdate(userid, chatid, last_index_in_chat);

  SendManyMsg(connection_cl, static_cast<uint32_t>(msg_type::SendUnpdateMore), static_cast<uint32_t>(msg_type::SendUnpdateFinish), texts);
}