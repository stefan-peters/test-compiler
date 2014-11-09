#ifndef ANNOTATION_ACTION_HPP
#define ANNOTATION_ACTION_HPP

#include "annotation_consumer.hpp"

#include <coverage/annotation.hpp>

#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendAction.h>

using namespace coverage;

class AnnotationAction : public clang::ASTFrontendAction {
 public:
  AnnotationAction(AnnotationList &annotations) : annotations_(annotations) {}

  virtual clang::ASTConsumer *CreateASTConsumer(
      clang::CompilerInstance &compiler, llvm::StringRef in_file) {
    return new AnnotationConsumer(&compiler.getASTContext(), annotations_);
  }

  AnnotationList &annotations_;
};

#endif
