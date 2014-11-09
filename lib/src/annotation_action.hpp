#ifndef ANNOTATION_ACTION_HPP
#define ANNOTATION_ACTION_HPP

#include "annotation_consumer.hpp"

#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendAction.h>

class AnnotationAction : public clang::ASTFrontendAction {
 public:
  virtual clang::ASTConsumer *CreateASTConsumer(
      clang::CompilerInstance &compiler, llvm::StringRef in_file) {
    return new AnnotationConsumer(&compiler.getASTContext());
  }
};

#endif
