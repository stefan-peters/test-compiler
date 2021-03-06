#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <stdio.h>

#include <coverage/instrument/default.h>

// access the internal data of the library
extern "C" {

const char* coverage_serialize_buffer(coverage_buffer_t* buffer);
void coverage_file_write_coverage();

extern const char* coverage_file_default_path;
extern const char* coverage_file_path_environment_variable;
extern unsigned int coverage_file_timestamp;

}

void trigger_data1_coverage();


COVERAGE_CREATE_BUFFER("write_file_test", 5);

TEST(cnt_file_tests, test_coverage_file_is_written) {

    unsetenv(coverage_file_path_environment_variable);
    remove(coverage_file_default_path);
    coverage_file_write_coverage();

    ASSERT_TRUE(access(coverage_file_default_path, F_OK ) != -1);
}


TEST(cnt_file_tests, test_environment_overwrite) {
    remove("my-coverage.dat");
    remove(coverage_file_default_path);

    setenv(coverage_file_path_environment_variable, "my-coverage.dat", 1);
    coverage_file_write_coverage();

    ASSERT_TRUE(access(coverage_file_default_path, F_OK ) == -1);
    ASSERT_TRUE(access("my-coverage.dat", F_OK ) != -1);

    unsetenv(coverage_file_path_environment_variable);
}


TEST(cnt_file_tests, test_counting) {

    remove(coverage_file_default_path);

    COVERAGE_INC(1);
    trigger_data1_coverage();

    coverage_file_write_coverage();

    ASSERT_TRUE(access(coverage_file_default_path, F_OK ) != -1);

    FILE* file = fopen(coverage_file_default_path, "r");
    ASSERT_TRUE(file != 0);

    char line[128];
    int lines = 0;

    char coverage_1[128];
    sprintf(coverage_1, "%u,data1.cpp,2,0,0,2\n", coverage_file_timestamp);

    char coverage_2[128];
    sprintf(coverage_2, "%u,write_file_test,0,1,0,0,0\n", coverage_file_timestamp);

    while(fgets(line, sizeof(line), file)) {
        ++lines;
        ASSERT_TRUE(
            strcmp(line, coverage_1) == 0 or
            strcmp(line, coverage_2) == 0
        );
    }

    ASSERT_EQ(lines, 2);
}
