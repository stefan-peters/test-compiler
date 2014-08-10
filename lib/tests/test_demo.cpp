#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <demo.h>

int sqr(int x) {
  return Value * x;
}


TEST(FirstTest, Call) {
  EXPECT_TRUE(sqr(1) == 1);
}  


// otool -L --> ldd