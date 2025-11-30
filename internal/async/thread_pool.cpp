#include "thread_pool.h"
#include <functional>
#include <iostream>
#include <ostream>
#include <stop_token>

ThreadPool::ThreadPool(size_t num_threads) {
  workers.reserve(num_threads);

  for (size_t i = 0; i < num_threads; i++) {
    workers.emplace_back(
        [this](std::stop_token stoken) { this->worker_loop(stoken); });
  }
}

ThreadPool::~ThreadPool() {
  // Request all jthreads to stop
  for (auto &t : workers)
    t.request_stop();

  // Push N empty tasks so blocked workers wake up
  for (size_t i = 0; i < workers.size(); ++i)
    task_queue.push(nullptr);
}

void ThreadPool::worker_loop(std::stop_token stoken) {
  while (!stoken.stop_requested()) {
    std::function<void()> task;

    if (task_queue.wait_and_pop(task, stoken)) {
      task();
    }
  }
}
