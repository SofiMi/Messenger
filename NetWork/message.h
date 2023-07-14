#pragma once
#include <cstring>
#include <iostream>
#include <memory>
#include <vector>
#include "net_connection.h"

struct message {
  static size_t now_id;
  size_t id;
  size_t size_ = 0;
  std::vector<char> body;

  message();
  size_t size() const;

  template <typename Data>
  void AddInfo(const Data &data);

  template <typename Data> 
  void ReturnInfo(Data &data);

  friend std::ostream &operator<<(std::ostream &os, const message &msg);
};

size_t message::now_id = 0;

message::message() { id = now_id++; }

template <typename Data>
void message::ReturnInfo(Data &data) {
  std::memcpy(&data, body.data() + body.size() - sizeof(data), sizeof(data));
  body.resize(body.size() - sizeof(data));
  size_ = body.size();
}

std::ostream &operator<<(std::ostream &os, const message &msg) {
  os << "ID: " << msg.id << "\nSize: " << msg.size();
  return os;
}

size_t message::size() const { return size_; }

template <typename Data>
void message::AddInfo(const Data &data) {
  body.resize(body.size() + sizeof(data));
  std::memcpy(body.data() + size_, &data, sizeof(data));
  size_ = body.size();
}

template <typename T>
struct owned_message {
  message msg;
  std::shared_ptr<connection<T>> remote = nullptr;

  template <typename U>
  friend std::ostream& operator<<(std::ostream &os, const owned_message<U>& msg);
};

template <typename U>
std::ostream& operator<<(std::ostream& os, const owned_message<U>& msg) {
  os << msg.msg;
  return os;
}