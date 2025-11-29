#pragma once

#include <mutex>
#include <queue>

template <typename T> class SafeQueue {
private:
  std::queue<T> queue;
  std::mutex mutex;

public:
  SafeQueue<T>();
  ~SafeQueue<T>() = default;

  void push(T val);
  bool try_pop(T &out);
  void wait_and_pop(T &out);
};

template <typename T> SafeQueue<T>::SafeQueue() : queue(), mutex(){};

template <typename T> void SafeQueue<T>::push(T val) {
  std::lock_guard<std::mutex> guard(mutex);
  queue.push(val);
};

template <typename T> bool SafeQueue<T>::try_pop(T &out) {
  std::lock_guard<std::mutex> guard(mutex);
  if (queue.empty()) {
    return false;
  }

  out = queue.pop();
  return true;
};

template <typename T> void SafeQueue<T>::wait_and_pop(T &out) {
  std::lock_guard<std::mutex> guard(mutex);
  out = queue.pop();
};
