#include "async/thread_pool.h"
#include <future>
#include <gtest/gtest.h>

TEST(ThreadPoolTest, SubmitTask) {
  size_t sz = 10;
  ThreadPool tp = ThreadPool(sz);
  std::future<int> res1 = tp.submit([](int a, int b) { return a + b; }, 10, 12);

  std::future<int> res2 = tp.submit([](int a, int b) { return a * b; }, 10, 12);
  std::future<int> res3 = tp.submit([](int a, int b) { return a * b; }, 10, 2);

  EXPECT_EQ(res1.get(), 22);
  EXPECT_EQ(res2.get(), 120);
  EXPECT_EQ(res3.get(), 20);
}
