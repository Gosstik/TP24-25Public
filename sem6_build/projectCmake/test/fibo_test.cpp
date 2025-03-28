#include <gtest/gtest.h>
#include "fibo.h"

TEST(FiboTests, Basic) {
  EXPECT_EQ(fibo(5), 5);
}


