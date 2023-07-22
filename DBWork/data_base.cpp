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
                             "where chatid is not NULL and chatname is not NULL and rank < " + std::to_string(count_before + 20) + " and rank > " + std::to_string(count_before);
  pqxx::nontransaction N(*connection);
  return N.exec((char*)req.c_str());
}

pqxx::result WorkDB::GetMessages(int chatid, int count_before) {
  std::string req = "with mess as (\n"
			              "select index_in_char, text from server.message\n"
			              "where chatid = ";
  req += std::to_string(chatid) + ")\n"
                                  "select index_in_char, text from mess\n"
                                  "where index_in_char is not NULL and text is not NULL and index_in_char > " + std::to_string(count_before  - 20) + " and index_in_char < " + std::to_string(count_before);
  
  pqxx::nontransaction N(*connection);
  return N.exec((char*)req.c_str());
}