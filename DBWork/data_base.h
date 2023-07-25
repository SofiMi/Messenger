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
  pqxx::result GetMessages(int chatid, int count_before);
  ~WorkDB();
  void InsertMsg(int chatid, int userid, const std::string& text);
  int AddNewUser(const std::vector<std::string>& user_info);

  int CountSameNick(const std::string& nick);
  int CountSameLogin(const std::string& login);

  pqxx::result GetUseridByChatitd(int chatid);
  int GetCountMsgInChat(int chat);
  int ChatIdByNameAndUserid(int userid, const std::string& name);
  std::pair<int, std::string> CreateNewChat(int userid, const std::string& name);
  int CheckTetAtTetChat(int userid, const std::string& name);
  pqxx::result GetDataUpdate(int userid, int chatid, int last_index_in_chat);
};