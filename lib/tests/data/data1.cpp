#include <coverage/instrument/default.h>

COVERAGE_CREATE_BUFFER("data1.cpp", 4);


void trigger_data1_coverage() {
    COVERAGE_INC(3);
    COVERAGE_INC(3);
    COVERAGE_INC(0);
    COVERAGE_INC(0);
}
