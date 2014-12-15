#include <sys/time.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include <coverage/instrument/default.h>
#include <coverage/instrument/impl/registry.h>

const char* coverage_default_file_path = "coverage.dat";
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

static FILE* c_file = 0;
static unsigned int c_timestamp = 0;

static void coverage_write_buffer_to_file(coverage_buffer_t* buffer) {
    fprintf(c_file, "%u,%s\n", c_timestamp, coverage_serialize_buffer(buffer));
}


COVERAGE_EXIT_FUNCTION
void coverage_write_coverage_to_file() {

    const char* path = getenv(coverage_file_path_environment_variable);
    if(! path) {
        path = coverage_default_file_path;
    }

    c_timestamp = (unsigned int) time(NULL);

    c_file = fopen(path, "a");
    if(! c_file) {
        fprintf(stderr, "COVERAGE: could not append data to %s: %s", path, strerror(errno));
        return;
    }

    coverage_file_iterate(coverage_write_buffer_to_file);
    fclose(c_file);

    c_file = 0;
}
