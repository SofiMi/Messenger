#pragma once
#include <iostream>
#include <pqxx/pqxx>

class WorkDB {
 pqxx::connection* connection;
 public:
  WorkDB();
  std::vector<int> GetChatFromUserId(int userid);
  ~WorkDB();
};