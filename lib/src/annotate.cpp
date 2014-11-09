#include <coverage/annotate.hpp>
#include "annotation_action.hpp"
#include <clang/Tooling/Tooling.h>

namespace coverage {

AnnotationList annotate(const std::string& code,
                        const ParameterList& parameter) {
  AnnotationList list;
  clang::tooling::runToolOnCodeWithArgs(new AnnotationAction(list), code, parameter);

  return list;
}
}
