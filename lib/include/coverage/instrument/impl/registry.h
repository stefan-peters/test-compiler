#ifndef COVERAGE_INSTRUMENT_IMPL_REGISTRY_H
#define COVERAGE_INSTRUMENT_IMPL_REGISTRY_H

/**
* DEFAULT IMPLEMENTATION for a coverage registry that can be used
* in custom implementations. Just include it in the c implementation
* file and the following functions are automatically implemented:
*  - coverage_buffer_register
*  - coverage_file_iterate
*/

#include <stdio.h>

typedef struct coverage_data_t {
    coverage_buffer_t* buffer;
    struct coverage_data_t* previous;
} coverage_data_t;

static coverage_data_t* coverage_last_node = 0;

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

#endif
