#include <coverage/annotate.hpp>
#include "annotation_action.hpp"
#include <clang/Tooling/Tooling.h>

namespace coverage {

Annotations annotate(const std::string& code, const Parameters& parameter) {
  Annotations annotations;
  clang::tooling::runToolOnCodeWithArgs(new AnnotationAction(&annotations),
                                        code, parameter);

  return annotations;
}
}
