#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <demo.h>

int sqr(int x) {
  return Value * x;
}


TEST(FirstTest, Call) {
  ASSERT_STREQ(xgreet(), "hello, world");
}  


// otool -L --> ldd