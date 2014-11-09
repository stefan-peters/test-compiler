#ifndef COVERAGE_INSTRUMENT_H
#define COVERAGE_INSTRUMENT_H

#include <string>
#include <vector>

namespace coverage {

struct Annotation {
  std::string name;
};

typedef std::vector<Annotation> AnnotationList;
typedef std::vector<std::string> ParameterList;


AnnotationList annotate(const std::string& code,
                        const ParameterList& parameter = ParameterList());
}

#endif
