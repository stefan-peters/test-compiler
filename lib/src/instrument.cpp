#include <coverage/instrument.h>
#include "annotation_action.hpp"
#include "clang/Tooling/Tooling.h"


namespace coverage {

std::string instrument(const std::string &code, const ParameterList &args) {
  clang::tooling::runToolOnCodeWithArgs(new AnnotationAction, code, args);
  return code;
}
}
