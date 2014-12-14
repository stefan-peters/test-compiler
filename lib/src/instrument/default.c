#include <coverage/instrument/default.h>
#include <coverage/instrument/impl/registry.h>

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

FILE* coverage_file = 0;

void coverage_write_to_file(coverage_buffer_t* buffer) {
    fprintf(coverage_file, "%s", coverage_serialize_buffer(buffer));
}


COVERAGE_EXIT_FUNCTION
void coverage_exit_handler() {

    coverage_file = fopen("coverage.dat", "a");
    coverage_file_iterate(coverage_write_to_file);
    fclose(coverage_file);
    
    coverage_file = 0;
}
