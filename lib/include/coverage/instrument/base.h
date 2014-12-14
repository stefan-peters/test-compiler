#ifndef COVERAGE_INSTRUMENT_BASE_H
#define COVERAGE_INSTRUMENT_BASE_H

/**
* This is the base header with the interface for all
* instrumentation code. This file must be not directly
* included
*/

#include <stdlib.h>

struct coverage_buffer_struct;
typedef struct coverage_buffer_struct coverage_buffer_t;

typedef void (*coverage_buffer_callback) (coverage_buffer_t*);

void coverage_buffer_register(coverage_buffer_t*);
const char* coverage_serialize_buffer(coverage_buffer_t*);

void coverage_file_iterate(coverage_buffer_callback);

#define COVERAGE_INIT_FUNCTION __attribute__((constructor))
#define COVERAGE_EXIT_FUNCTION __attribute__((destructor))

#define COVERAGE_REGISTER_BUFFER(buffer) \
COVERAGE_INIT_FUNCTION \
static void coverage_init_function() { \
    coverage_buffer_register(&buffer); \
}

#endif
