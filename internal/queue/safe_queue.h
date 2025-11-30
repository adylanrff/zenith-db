#pragma once

#include <algorithm>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <utility>

template <typename T> class SafeQueue {
private:
  std::queue<T> queue;
  std::mutex mutex;

  std::condition_variable cv;

public:
  SafeQueue();
  ~SafeQueue() = default;

  void push(T val);
  bool try_pop(T &out);
  void wait_and_pop(T &out);
};

template <typename T> SafeQueue<T>::SafeQueue() : queue(), mutex(){};

template <typename T> void SafeQueue<T>::push(T val) {
  std::lock_guard guard(mutex);
  queue.push(std::move(val));
  cv.notify_one();
};

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
