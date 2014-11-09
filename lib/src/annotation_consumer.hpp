#ifndef ANNOTATION_CONSUMER_HPP
#define ANNOTATION_CONSUMER_HPP

#include "annotation_visitor.hpp"
#include <clang/AST/ASTConsumer.h>

class AnnotationConsumer : public clang::ASTConsumer {
 public:
  explicit AnnotationConsumer(clang::ASTContext *context) : visitor_(context) {}

  virtual void HandleTranslationUnit(clang::ASTContext &Context) {
    visitor_.TraverseDecl(Context.getTranslationUnitDecl());
  }

 private:
  AnnotationVisitor visitor_;
};

#endif
