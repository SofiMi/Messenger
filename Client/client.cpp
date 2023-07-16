#include "client.h"
#include <iostream>

std::vector<int> Client::GetChat(size_t max_users, size_t users_before) {
  std::vector<int> res;
  for (int i = 0; i < max_users; i++) {
    res.push_back(i);
  }
  return res;
}