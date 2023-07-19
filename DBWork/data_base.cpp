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
/* Create SQL statement */
  const char* sql = "select chatid from server.chat\n"
                    "where userid = 1";

  /* Create a non-transactional object. */
  pqxx::nontransaction N(*connection);
  
  /* Execute SQL query */
  pqxx::result result_select(N.exec(sql));

  std::vector<int> result(result_select.size());
  
  /* List down all the records */
  int i = 0;
  for (auto row = result_select.begin(); row != result_select.end(); ++row, ++i) {
    result[i] = row[0].as<int>();
  }
  return result;
}