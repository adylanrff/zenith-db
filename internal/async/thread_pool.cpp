#include "thread_pool.h"
#include <stop_token>

ThreadPool::ThreadPool(size_t num_threads) {
  workers.reserve(num_threads);

  for (size_t i = 0; i < num_threads; i++) {
    workers.emplace_back(
        [this](std::stop_token stoken) { this->worker_loop(stoken); });
  }
}

void ThreadPool::worker_loop(std::stop_token stoken) {
  while (!stoken.stop_requested()) {
    std::function<void()> task;

    if (task_queue.wait_and_pop(task, stoken)) {
      task();
    }
  }
}
