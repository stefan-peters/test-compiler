#include "gmock/gmock.h"
#include "gtest/gtest.h"

// while( (cond) ? ++[X], true : ++[X], false)
// if - else
// for(;;)
// do while
// :?

// break
// continue
// return 
// goto
// throw

// for(e:c)
// compound statement

// label
// catch 
// switch 
// case 
// default

//and or && ||

// function
// statement
// branch
// condition

#define COV_BRANCH(condition, true_counter, false_counter) \
 (condition) ? (++true_counter, true) : (++false_counter, false)

#define COV_STMT(stmt, counter) \
 ++counter; stmt

bool run_if_stmt(bool branch, int& true_c, int& false_c) {
	if(COV_BRANCH(branch, true_c, false_c))  {
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


TEST(stmt_test, test_common_use_cases) {
	int counter = 0;

	COV_STMT(int destination = 5;, counter);

	EXPECT_EQ(destination, 5);
	EXPECT_EQ(counter, 1);

	#define COMMA ,
	COV_STMT(int dest2 COMMA dest3 = 5;, counter);

	EXPECT_EQ(dest3, 5);
	EXPECT_EQ(counter, 2);	
}