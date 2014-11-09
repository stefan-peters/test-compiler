#ifndef ANNOTATION_VISITOR_HPP
#define ANNOTATION_VISITOR_HPP

#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/AST/ASTContext.h>

#include <coverage/annotation.hpp>

using namespace clang;
using namespace coverage;

class AnnotationVisitor : public RecursiveASTVisitor<AnnotationVisitor> {
 public:
  explicit AnnotationVisitor(ASTContext* context,
                             coverage::AnnotationList& annotations)
      : context_(context), annotations_(annotations) {}

  bool VisitIfStmt(IfStmt* stmt);

 private:
  ASTContext* context_;
  AnnotationList& annotations_;
};

#endif
