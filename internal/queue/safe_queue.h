#pragma once

#include <algorithm>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <stop_token>
#include <utility>

template <typename T> class SafeQueue {
private:
  std::queue<T> queue;
  std::mutex mutex;

  std::condition_variable_any cv;

public:
  SafeQueue();
  ~SafeQueue() = default;

  void push(T val);
  bool try_pop(T &out);
  void wait_and_pop(T &out);
  bool wait_and_pop(T &out, std::stop_token stoken);
};

template <typename T> SafeQueue<T>::SafeQueue() : queue(), mutex(){};

template <typename T> bool SafeQueue<T>::try_pop(T &out) {
  std::lock_guard guard(mutex);
  if (queue.empty()) {
    return false;
  }

  out = std::move(queue.front());
  queue.pop();
  return true;
};

template <typename T> void SafeQueue<T>::wait_and_pop(T &out) {
  std::unique_lock ul(mutex);
  cv.wait(ul, [this] { return !queue.empty(); });

  out = std::move(queue.front());
  queue.pop();
};

template <typename T> void SafeQueue<T>::push(T val) {
  std::lock_guard guard(mutex);
  queue.push(std::move(val));
  cv.notify_all();
}

template <typename T>
bool SafeQueue<T>::wait_and_pop(T &out, std::stop_token stoken) {
  std::unique_lock ul(mutex);

  // Wait returns true if predicate is true (queue has data)
  // Wait returns false if stop requested AND queue is empty
  if (cv.wait(ul, stoken, [this] { return !queue.empty(); })) {
    out = std::move(queue.front());
    queue.pop();
    return true;
  }

  return false;
}
