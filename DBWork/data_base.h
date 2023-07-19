#pragma once
#include <iostream>
#include <pqxx/pqxx>
#include <vector>
#include <array>

class WorkDB {
 pqxx::connection* connection;
 public:
  WorkDB();
  std::vector<int> GetChatFromUserId(int userid);
  ~WorkDB();
};