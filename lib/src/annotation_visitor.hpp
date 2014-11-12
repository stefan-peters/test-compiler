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
                             coverage::Annotations* annotations)
      : context_(context), annotations_(annotations) {}

  bool VisitIfStmt(IfStmt* stmt);

 private:
  Position getPosition(const SourceLocation& loc) const;
  Range getRange(const Stmt* smt) const;

  ASTContext* context_;
  Annotations* annotations_;
};

#endif
