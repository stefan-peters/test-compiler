#ifndef COVERAGE_INSTRUMENT_H
#define COVERAGE_INSTRUMENT_H

#include <string>
#include <vector>

#include <coverage/annotation.hpp>

namespace coverage {

typedef std::vector<std::string> ParameterList;

AnnotationList annotate(const std::string& code,
                        const ParameterList& parameter = ParameterList());
}

#endif
