#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <coverage/instrument/default.h>

// extern "C" {
//
// const char* coverage_serialize_buffer(coverage_buffer_t* buffer);
//
// }


COVERAGE_CREATE_BUFFER("123456", 5);

TEST(base_tests, test_file_writing) {
    COVERAGE_INC(2);
}
