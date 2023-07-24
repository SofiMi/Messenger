#include "data_base.h"

WorkDB::WorkDB() {
  try {
    connection = new pqxx::connection("dbname = server " 
                                      "user = postgres "
                                      "password = postgres "
                                      "hostaddr = 127.0.0.1 "
                                      "port = 5432");
    if (connection->is_open()) {
      std::cout << "Opened database successfully: " << connection->dbname() << std::endl;
    } else {
      std::cout << "Can't open database" << std::endl;
      throw;
    }
  } catch (const std::exception &e) {
    std::cerr << "YES" << e.what() << std::endl;
    throw;
  }
}

WorkDB::~WorkDB(){
  connection->disconnect();
  delete connection;
}

std::vector<int> WorkDB::GetChatFromUserId(int userid) {
  const char* sql = "select chatid from server.chat\n"
                    "where userid = 1";
  pqxx::nontransaction N(*connection);
  pqxx::result result_select(N.exec(sql));
  std::vector<int> result(result_select.size());
  int i = 0;
  for (auto row = result_select.begin(); row != result_select.end(); ++row, ++i) {
    result[i] = row[0].as<int>();
  }
  return result;
}

int WorkDB::GetIdByLogin(const std::string& login) {
  std::string req = "select userid from server.user\n where login = '";
  req += login + "'";
  pqxx::nontransaction N(*connection);
  pqxx::result result_select(N.exec((char*)req.c_str()));

  if (result_select.size() == 0) {
    return -1;
  } else {
    return result_select.begin()[0].as<int>();
  }
}

bool WorkDB::CheckPassword(const std::string& password, int id) {
  std::string req = "select userid from server.user\n"
                    "where login = '";
  req += password + "' and userid = " + std::to_string(id);
  pqxx::nontransaction N(*connection);
  pqxx::result result_select(N.exec((char*)req.c_str()));
  return result_select.size() != 0;
}

bool WorkDB::SetNewUser(const std::string& login, const std::string& password, const std::string& name) {
  std::string req = "select max(userid) from server.user";
  pqxx::nontransaction N(*connection);
  pqxx::result result_select(N.exec(req.c_str()));
  int new_id = result_select.begin()[0].as<int>();

  req = "insert into server.user\n"
          "values (" + std::to_string(new_id) + "'" + name + "', '" + login + "', '" + password + ")";

  pqxx::work W(*connection);
  W.exec(req.c_str());
  return true;
}

bool WorkDB::Update(int userid, const std::string& new_data, const std::string& what_update) {
  std::string req = "update server.user set " + what_update + " = '" + new_data + "' where userid = " + std::to_string(userid);
  pqxx::work W(*connection);
  W.exec(req.c_str());
  return true;
}

pqxx::result WorkDB::GetChat(int id, int count_before) {
  std::string req = "with chat_id as (\n"
						        "select chatid from server.chat\n"
						        "where userid = ";
  req += std::to_string(id) + " ), \n"
                             "res as (\n"
		                         "select server.chatname.chatid as chatid, chatname,\n" 
                             "rank() OVER (order by  server.chatname.chatid desc) as rank from chat_id\n"
		                         "left join server.chatname\n"
		                         "on  server.chatname.chatid = chat_id.chatid\n)\n"
                             "select chatid, chatname from res\n"
                             "where chatid is not NULL and chatname is not NULL and rank < " + std::to_string(count_before + 30) + " and rank >= " + std::to_string(count_before);
  pqxx::nontransaction N(*connection);
  return N.exec((char*)req.c_str());
}

pqxx::result WorkDB::GetMessages(int chatid, int count_before) {
  std::string req = "with mess as (\n"
			              "select index_in_char, text from server.message\n"
			              "where chatid = ";
  req += std::to_string(chatid) + ")\n"
                                  "select index_in_char, text from mess\n"
                                  "where index_in_char is not NULL and text is not NULL and index_in_char >= " + std::to_string(count_before  - 20) + " and index_in_char < " + std::to_string(count_before);
  
  pqxx::nontransaction N(*connection);
  return N.exec((char*)req.c_str());
}

void WorkDB::InsertMsg(int chatid, int userid, const std::string& text) {
  /* Добавление нового сообщения в базу данных. */
  pqxx::work W(*connection);

  std::string messageid_req = "select max(messageid) + 1 from server.message";
  pqxx::result messageid_res = W.exec((char*)messageid_req.c_str());
  int messageid = messageid_res.begin()[0].as<int>();

  std::string index_in_chat_req = "select max(index_in_char) + 1 from server.message";
  pqxx::result index_in_chat_res = W.exec((char*)index_in_chat_req.c_str());
  int index_in_chat = index_in_chat_res.begin()[0].as<int>();

  std::string insert = "insert into server.message (messageid, chatid, userid, index_in_char, text)\n";
  insert += "values (" + std::to_string(messageid) + ", " + std::to_string(chatid) + ", " + std::to_string(userid) + ", " + std::to_string(index_in_chat) + ", '" +  text + "')";
  W.exec(insert.c_str());
  W.commit();
}

int WorkDB::AddNewUser(const std::vector<std::string>& user_info) {
  /*  Регистрация нового пользователя.

    std::vector<std::string> user_info = {
      login,
      password,
      name,
      nickname
    }
  */
  pqxx::work W(*connection);
  std::string id_req = "select max(userid) + 1 from server.user";
  pqxx::result id_res = W.exec((char*)id_req.c_str());
  int userid = id_res.begin()[0].as<int>();

  std::string insert = "insert into server.user (userid, login, password, name, nickname)\n";
  insert += "values (" + std::to_string(userid) + ", '" + user_info[0] + "', '" + user_info[1] + "', '" + user_info[2] + "', '" +  user_info[3] + "')";
  W.exec(insert.c_str());
  W.commit();

  return userid;
}

int WorkDB::CountSameNick(const std::string& nick) {
  /* Количество таких же никнеймов. 0/1*/
  pqxx::work W(*connection);
  std::string req = "select count(*) from server.user\n"
                      "where nickname = '" + nick + "'";
  pqxx::result res = W.exec((char*)req.c_str());
  return res.begin()[0].as<int>();
}

int WorkDB::CountSameLogin(const std::string& login) {
  /* Количество таких же логинов. 0/1*/
  pqxx::work W(*connection);
  std::string req = "select count(*) from server.user\n"
                      "where login = '" + login + "'";
  pqxx::result res = W.exec((char*)req.c_str());
  return res.begin()[0].as<int>();
}

pqxx::result WorkDB::GetUseridByChatitd(int chatid) {
  pqxx::work W(*connection);
  std::string req = "select userid from server.chat\n"
                    "where chatid = " + std::to_string(chatid);
  pqxx::result res = W.exec((char*)req.c_str());
  return res;
}

int WorkDB::GetCountMsgInChat(int chatid) {
  pqxx::work W(*connection);
  std::string req = "select max(index_in_char) + 1 from server.message\n"
                    "where chatid = " + std::to_string(chatid);
  pqxx::result res = W.exec((char*)req.c_str());
  return res.begin()[0].as<int>();
}