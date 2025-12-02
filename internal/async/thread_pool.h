#pragma once

#include "queue/safe_queue.h"
#include <functional>
#include <future>
#include <memory>
#include <stop_token>
#include <thread>
#include <type_traits>
#include <utility>
#include <vector>

class ThreadPool {
private:
  SafeQueue<std::function<void()>> task_queue;
  std::vector<std::jthread> workers;

  void worker_loop(std::stop_token stoken);

public:
  explicit ThreadPool(size_t num_threads);

  template <typename Func, typename... Args>
  auto submit(Func &&f, Args &&...args) {
    using ReturnType = std::invoke_result_t<Func, Args...>;

    auto task = std::make_shared<std::packaged_task<ReturnType()>>(
        std::bind(std::forward<Func>(f), std::forward<Args>(args)...));

    std::future<ReturnType> res = task->get_future();

    task_queue.push([task]() { (*task)(); });
    return res;
  }
};
