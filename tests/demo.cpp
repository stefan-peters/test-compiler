#include "gmock/gmock.h"
#include "gtest/gtest.h"

int sqr(int x) {
  return x * x;
}


TEST(FirstTest, Call) {
  EXPECT_TRUE(sqr(1) == 1);
}  


int main(int argc, char** argv) {
  // The following line must be executed to initialize Google Mock
  // (and Google Test) before running the tests.
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}

// otool -L --> ldd