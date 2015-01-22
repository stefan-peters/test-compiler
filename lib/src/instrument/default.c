#include <sys/time.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include <coverage/instrument/default.h>
#include <coverage/instrument/impl/registry.h>

const char* coverage_file_default_path = "coverage.dat";
const char* coverage_file_path_environment_variable = "COVERAGE_FILE_PATH";

const char* coverage_serialize_buffer(coverage_buffer_t* buffer) {
    static char string[1024] = {0}; // @TODO this is bad! change it!

    int node = 0;
    int index = 0;

    index += sprintf(string, "%s", buffer->identifier);

    for(node = 0; node < buffer->length; ++node) {
        index += sprintf(&string[index], ",%d", buffer->nodes[node]);
    }

    return string;
}

static FILE* coverage_file_fp = 0;
unsigned int coverage_file_timestamp = 0;

static void coverage_write_buffer_to_file(coverage_buffer_t* buffer) {
    fprintf(coverage_file_fp, "%u,%s\n", coverage_file_timestamp, coverage_serialize_buffer(buffer));
}


COVERAGE_EXIT_FUNCTION
void coverage_file_write_coverage() {

    const char* path = getenv(coverage_file_path_environment_variable);
    if(! path) {
        path = coverage_file_default_path;
    }

    coverage_file_timestamp = (unsigned int) time(NULL);

    coverage_file_fp = fopen(path, "a");
    if(! coverage_file_fp) {
        fprintf(stderr, "COVERAGE: could not append data to %s: %s", path, strerror(errno));
        return;
    }

    coverage_file_iterate(coverage_write_buffer_to_file);
    fclose(coverage_file_fp);

    coverage_file_fp = 0;
}
