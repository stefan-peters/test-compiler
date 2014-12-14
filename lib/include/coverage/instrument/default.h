#ifndef COVERAGE_INSTRUMENT_DEFAULT_H
#define COVERAGE_INSTRUMENT_DEFAULT_H

#include <coverage/instrument/base.h>

typedef unsigned int coverage_counter_t;

struct coverage_buffer_struct {
    const char* identifier;

    coverage_counter_t* nodes;
    unsigned int length;
};

// creates the per-file coverage buffer
#define COVERAGE_CREATE_BUFFER(IDENTIFIER, SIZE) \
    static coverage_counter_t _coverage_counter[SIZE] = {0}; \
    static coverage_buffer_t _coverage_buffer = {IDENTIFIER, _coverage_counter, SIZE}; \
    COVERAGE_REGISTER_BUFFER(_coverage_buffer)


// increment the coverage node
#define COVERAGE(N) _coverage_counter[N]
#define COVERAGE_INC(N) ++COVERAGE(N)

#include <coverage/instrument/defines.h>

#endif
