#include <coverage/annotate.hpp>
#include "annotation_action.hpp"
#include "clang/Tooling/Tooling.h"

namespace coverage {

AnnotationList annotate(const std::string& code,
                        const ParameterList& parameter) {
  clang::tooling::runToolOnCodeWithArgs(new AnnotationAction, code, parameter);

  AnnotationList list;
  Annotation ano;
  ano.name = "if";
  list.push_back(ano);

  return list;
}
}
