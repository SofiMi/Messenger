#include <iostream>
#include <vector>
#include <cstring>

struct message {
  static size_t now_id;
  size_t id;
  size_t size_ = 0;
  std::vector<char> body;

  message() { id = now_id++; }
  size_t size() const { return size_; }

  template <typename Data>
  void AddInfo(const Data& data) {
    body.resize(body.size() + sizeof(data));
    std::memcpy(body.data() + size_, &data, sizeof(data));
    size_ = body.size();
  }

  template <typename Data>
  void ReturnInfo(Data& data) {
    std::memcpy(&data, body.data() + body.size() - sizeof(data), sizeof(data));
    body.resize(body.size() - sizeof(data));
    size_ = body.size();
  }

  friend std::ostream& operator<<(std::ostream& os, const message& msg) {
    os << "ID: " << msg.id << "\nSize: " << msg.size();
    return os;
  }
};

size_t message::now_id = 0;