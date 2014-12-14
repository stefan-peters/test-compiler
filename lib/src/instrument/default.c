#include <coverage/instrument/default.h>

#include <stdio.h>

typedef struct coverage_data_struct {
    coverage_buffer_t* buffer;
    struct coverage_data_struct* previous;
} coverage_data_t;

coverage_data_t* coverage_last_node = 0;

void coverage_buffer_register(coverage_buffer_t* buffer) {

    coverage_data_t* node = (coverage_data_t*) malloc(sizeof(coverage_data_t));

    node->buffer = buffer;
    node->previous = coverage_last_node;
    coverage_last_node = node;
}

void coverage_file_iterate(coverage_buffer_callback callback) {
    coverage_data_t* node = coverage_last_node;

    while(node) {
        callback(node->buffer);
        node = node->previous;
    }
}

const char* coverage_serialize_buffer(coverage_buffer_t* buffer) {
    static char string[1024] = {0}; // this is bad!

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
