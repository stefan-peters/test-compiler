#ifndef COVERAGE_INSTRUMENT_CHECK_INTERFACE_H
#define COVERAGE_INSTRUMENT_CHECK_INTERFACE_H

#ifndef COVERAGE_CREATE_BUFFER
#error Please define COVERAGE_CREATE_BUFFER(IDENTIFIER, SIZE) before including
#endif

#ifndef COVERAGE
#error Please define COVERAGE(INDEX) before including
#endif

#ifndef COVERAGE_INC
#error Please define COVERAGE_INC(INDEX) before including
#endif

// increment the true or the false node based on the condition
#define COVERAGE_BRANCH(condition, N1, N2) \
(condition) ? (COVERAGE_INC(N1), 1) : (COVERAGE_INC(N2), 0)

// this is done by the instrumenter to make it possible to
// have conditions with a comma inside it
#define COVERAGE_COMMA ,

#endif
