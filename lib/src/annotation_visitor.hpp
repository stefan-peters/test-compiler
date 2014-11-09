#ifndef ANNOTATION_VISITOR_HPP
#define ANNOTATION_VISITOR_HPP

#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/AST/ASTContext.h>

class AnnotationVisitor : public clang::RecursiveASTVisitor<AnnotationVisitor> {
 public:
  explicit AnnotationVisitor(clang::ASTContext* context) : context_(context) {}

 private:
  clang::ASTContext* context_;
};

#endif
