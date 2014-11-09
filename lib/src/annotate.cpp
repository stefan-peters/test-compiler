#include <coverage/annotate.hpp>
#include "annotation_action.hpp"
#include "clang/Tooling/Tooling.h"

namespace coverage {

std::string annotate(const std::string &code) {
  clang::tooling::runToolOnCodeWithArgs(new AnnotationAction, code,
                                        ParameterList());
  return code;
}
}
