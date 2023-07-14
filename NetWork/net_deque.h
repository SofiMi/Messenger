#pragma once
#include <deque>
#include <mutex>
#include <condition_variable>

template <typename T>
class net_deque {
 public:
  net_deque() = default;
  net_deque(const net_deque<T> &) = delete;
  virtual ~net_deque() { clear(); }

  void push_back(const T& item);
  void push_front(const T& item);
  const T& front();
  const T& back();
  T pop_front();
  T pop_back();
  bool empty();
  size_t count();
  void clear();
  void wait();

protected:
  std::mutex muxQueue;
  std::deque<T> deqQueue;
  std::condition_variable cvBlocking;
  std::mutex muxBlocking;
};

template <typename T>
const T& net_deque<T>::front() {
  std::scoped_lock lock(muxQueue);
  return deqQueue.front();
}

template <typename T>
const T& net_deque<T>::back() {
  std::scoped_lock lock(muxQueue);
  return deqQueue.back();
}

template <typename T>
T net_deque<T>::pop_front() {
  std::scoped_lock lock(muxQueue);
  auto t = std::move(deqQueue.front());
  deqQueue.pop_front();
  return t;
}

template <typename T>
T net_deque<T>::pop_back() {
  std::scoped_lock lock(muxQueue);
  auto t = std::move(deqQueue.back());
  deqQueue.pop_back();
  return t;
}

template <typename T>
void net_deque<T>::push_back(const T &item) {
  std::scoped_lock lock(muxQueue);
  deqQueue.emplace_back(std::move(item));

  std::unique_lock<std::mutex> ul(muxBlocking);
  cvBlocking.notify_one();
}

template <typename T>
void net_deque<T>::push_front(const T &item) {
  std::scoped_lock lock(muxQueue);
  deqQueue.emplace_front(std::move(item));

  std::unique_lock<std::mutex> ul(muxBlocking);
  cvBlocking.notify_one();
}

template <typename T>
bool net_deque<T>::empty() {
  std::scoped_lock lock(muxQueue);
  return deqQueue.empty();
}

template <typename T>
size_t net_deque<T>::count() {
  std::scoped_lock lock(muxQueue);
  return deqQueue.size();
}

template <typename T>
void net_deque<T>::clear() {
  std::scoped_lock lock(muxQueue);
  deqQueue.clear();
}

template <typename T>
void net_deque<T>::wait() {
  while (empty()) {
    std::unique_lock<std::mutex> ul(muxBlocking);
    cvBlocking.wait(ul);
  }
}