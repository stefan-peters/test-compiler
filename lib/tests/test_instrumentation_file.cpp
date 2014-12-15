#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <stdio.h>

#include <coverage/instrument/default.h>

// access the internal data of the library
extern "C" {

const char* coverage_serialize_buffer(coverage_buffer_t* buffer);
void coverage_write_coverage_to_file();

extern const char* coverage_default_file_path;
extern const char* coverage_file_path_environment_variable;

}

COVERAGE_CREATE_BUFFER("write_file_test", 5);

TEST(base_tests, test_coverage_file_is_written) {

    unsetenv(coverage_file_path_environment_variable);
    remove(coverage_default_file_path);
    coverage_write_coverage_to_file();

    ASSERT_TRUE(access(coverage_default_file_path, F_OK ) != -1);
}


TEST(base_tests, test_environment_overwrite) {
    remove("my-coverage.dat");
    remove(coverage_default_file_path);

    setenv(coverage_file_path_environment_variable, "my-coverage.dat", 1);
    coverage_write_coverage_to_file();

    ASSERT_TRUE(access(coverage_default_file_path, F_OK ) == -1);
    ASSERT_TRUE(access("my-coverage.dat", F_OK ) != -1);

    unsetenv(coverage_file_path_environment_variable);
}
