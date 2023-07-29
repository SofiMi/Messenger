#ifndef NET_QUEUE
#define NET_QUEUE

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
  class ts_queue {
  public:
    ts_queue() = default;
    ts_queue(const ts_queue &) = delete;
    virtual ~ts_queue() { clear(); }

  public:
    const T &front() {
      std::scoped_lock lock(mux_queue);
      return deqQueue.front();
    }

    const T &back()
    {
      std::scoped_lock lock(mux_queue);
      return deqQueue.back();
    }


    T pop_front()
    {
      std::scoped_lock lock(mux_queue);
      auto t = std::move(deqQueue.front());
      deqQueue.pop_front();
      return t;
    }


    T pop_back()
    {
      std::scoped_lock lock(mux_queue);
      auto t = std::move(deqQueue.back());
      deqQueue.pop_back();
      return t;
    }


    void push_back(const T &item)
    {
      std::scoped_lock lock(mux_queue);
      deqQueue.push_back(std::move(item));

      std::unique_lock<std::mutex> ul(mux_blocking);
      cvBlocking.notify_one();
    }


    void push_front(const T &item)
    {
      std::scoped_lock lock(mux_queue);
      deqQueue.push_front(std::move(item));

      std::unique_lock<std::mutex> ul(mux_blocking);
      cvBlocking.notify_one();
    }


    bool empty()
    {
      std::scoped_lock lock(mux_queue);
      return deqQueue.empty();
    }


    size_t count()
    {
      std::scoped_lock lock(mux_queue);
      return deqQueue.size();
    }

  
    void clear()
    {
      std::scoped_lock lock(mux_queue);
      deqQueue.clear();
    }

    void wait()
    {
      while (empty()) {
        std::unique_lock<std::mutex> ul(mux_blocking);
        cvBlocking.wait(ul);
      }
    }

  protected:
    std::mutex mux_queue;
    std::deque<T> deqQueue;
    std::condition_variable cvBlocking;
    std::mutex mux_blocking;
  };
}    // namespace net

#endif