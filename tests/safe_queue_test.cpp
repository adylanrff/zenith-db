#include "queue/safe_queue.h"
#include <gtest/gtest.h>

TEST(SafeQueueTest, PushAndTryPop) {
  // SafeQueue<int> q;
  // q.push(42);
  //
  // int val = 0;
  // bool success = q.pop(val);
  //
  // EXPECT_TRUE(success);
  // EXPECT_EQ(val, 42);
}

TEST(SafeQueueTest, PushAndWaitPop) {
  // SafeQueue<int> q;
  // q.push(42);
  //
  // int val = 0;
  // q.pop(val);
  //
  // EXPECT_EQ(val, 42);
}
