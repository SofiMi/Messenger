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
  msg.header.userid = userid_;

  for (size_t i = 0; i < password.size(); ++i) {
    msg.data[i] = password[i];
  }
  send(msg);
}

void Client::SetUserid(int userid) {
  userid_ = userid;
}

std::vector<std::string> Client::GetFriend(size_t count, bool& other_fr) {
  other_fr = true;
  return {{"Sofi"}, {"Tony"}};
}

std::vector<std::string> Client::GetMessage(size_t count, bool& other_fr) {
  other_fr = true;
  return { {"задумайся, зачем компании берут стажеров. ты работал n месяцев, узнал домен проекта, "
            "закрывал задачи, знаком с командой — зачем компании тебя куда-то отпускать?"},
           {"ну я поэтому говорю про компанию в целом, даже если в команде нет мест зачем тебя выпускать в рынок обратно"},
           {"Эт понятно, просто интересно, когда компании нанимают"
           "весьма большое количество стажеров, неужели у них столько вакантных мест?"
            "Либо устраивают между стажерами схватку"}, 
            };
}