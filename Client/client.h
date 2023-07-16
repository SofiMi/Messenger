#pragma once
#include <vector>

class Client {
  public:
    std::vector<int> GetChat(size_t max_users, size_t users_before);
};