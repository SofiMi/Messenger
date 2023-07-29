#ifndef NET_MESSAGE
#define NET_MESSAGE

#include <memory>
#include <thread>
#include <mutex>
#include <deque>
#include <string>
#include <iostream>
#include <chrono>
#include <limits>
#include <array>

#define ASIO_STANDALONE
#include <boost/asio.hpp>

namespace net {

  template <typename T>
  struct message_header {
    T id{};
    std::array<char, 256> name{};
		int userid;
  };

  template <typename T>
  struct message {
    message_header<T> header{};
    std::array<char, 256> data{};    // message content
    std::chrono::system_clock::time_point time = std::chrono::system_clock::now();
  };


  template <typename T>
  class connection;

  template <typename T>
  struct owned_message {
    std::shared_ptr<connection<T>> remote = nullptr;
    message<T> msg;

    friend std::ostream &operator<<(std::ostream &os, const owned_message<T> &msg)
    {
      os << msg.msg;
      return os;
    }
  };
}    // namespace net

#endif