#ifndef ANNOTATION_VISITOR_HPP
#define ANNOTATION_VISITOR_HPP

#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/AST/ASTContext.h>

using namespace clang;

class AnnotationVisitor : public RecursiveASTVisitor<AnnotationVisitor> {
 public:
  explicit AnnotationVisitor(ASTContext* context) : context_(context) {}

  bool VisitIfStmt(IfStmt* stmt);

 private:
  ASTContext* context_;
};

#endif
