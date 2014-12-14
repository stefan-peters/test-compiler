#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <coverage/instrument/default.h>

COVERAGE_CREATE_BUFFER("123456", 5);

coverage_buffer_struct* data;

void coverage_buffer_register(coverage_buffer_struct* buffer) {
    data = buffer;
}

TEST(base_tests, test_initialisation) {
    ASSERT_TRUE(data);

    ASSERT_EQ(data->length, 5);
    ASSERT_STREQ(data->identifier, "123456");
}


TEST(base_tests, test_count_increment) {
    ASSERT_EQ(COVERAGE(1), 0);
    COVERAGE_INC(1);
    ASSERT_EQ(COVERAGE(1), 1);
}

TEST(base_tests, test_branch_increment) {
    ASSERT_EQ(COVERAGE(2), 0);

    COVERAGE_BRANCH(true, 2, 3);
    ASSERT_EQ(COVERAGE(2), 1);
    ASSERT_EQ(COVERAGE(3), 0);

    COVERAGE_BRANCH(false, 2, 3);
    ASSERT_EQ(COVERAGE(2), 1);
    ASSERT_EQ(COVERAGE(3), 1);    
}
