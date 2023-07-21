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
  int GetIdByLogin(const std::string& wlogin);
  bool CheckPassword(const std::string& wpassword, int id);
  bool Update(int userid, const std::string& new_data, const std::string& what_update);
  bool SetNewUser(const std::string& login, const std::string& password, const std::string& name);
  pqxx::result GetChat(int id, int count_before);
  ~WorkDB();
};