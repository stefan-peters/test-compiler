#include "gmock/gmock.h"
#include "gtest/gtest.h"

bool run_if_stmt(bool branch, int& true_c, int& false_c) {
	if( (branch) ? (++true_c, true) : (++false_c, false) )  {
		return true;
	}
	else {
		return false;
	}
}

TEST(if_test, test_true) {
	int true_c = 0;
	int false_c = 0;

	EXPECT_TRUE(run_if_stmt(true, true_c, false_c));
	EXPECT_EQ(true_c, 1);
	EXPECT_EQ(false_c, 0);
}

TEST(if_test, test_false) {
	int true_c = 0;
	int false_c = 0;

	EXPECT_FALSE(run_if_stmt(false, true_c, false_c));
	EXPECT_EQ(true_c, 0);
	EXPECT_EQ(false_c, 1);
}