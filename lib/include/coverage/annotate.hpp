#ifndef COVERAGE_INSTRUMENT_H
#define COVERAGE_INSTRUMENT_H

#include <string>
#include <vector>

#include <coverage/annotation.hpp>

namespace coverage {

typedef std::vector<std::string> Parameters;

Annotations annotate(const std::string& code,
                     const Parameters& parameter = Parameters());
}

#endif
