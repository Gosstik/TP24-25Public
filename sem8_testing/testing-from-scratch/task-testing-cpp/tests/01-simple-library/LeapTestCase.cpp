#include "LeapTestCase.h"

#include <Functions.h>


TEST_F(LeapTestCase, InvalidValues) {
  EXPECT_THROW(IsLeap(-1), std::invalid_argument);
}

TEST_F(LeapTestCase, JustWorks) {
  EXPECT_FALSE(IsLeap(1));
  EXPECT_TRUE(IsLeap(4));
}

TEST(GetMonthDaysTestCase, JustWorks) {
  EXPECT_EQ(GetMonthDays(2015, 4), 30);
}
