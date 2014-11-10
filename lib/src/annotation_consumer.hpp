#ifndef ANNOTATION_CONSUMER_HPP
#define ANNOTATION_CONSUMER_HPP

#include "annotation_visitor.hpp"

#include <coverage/annotation.hpp>

#include <clang/AST/ASTConsumer.h>

using namespace coverage;

class AnnotationConsumer : public clang::ASTConsumer {
 public:
  explicit AnnotationConsumer(clang::ASTContext *context,
                              Annotations *annotations_)
      : visitor_(context, annotations_) {}

  virtual void HandleTranslationUnit(clang::ASTContext &Context) {
    visitor_.TraverseDecl(Context.getTranslationUnitDecl());
  }

 private:
  AnnotationVisitor visitor_;
};

#endif
