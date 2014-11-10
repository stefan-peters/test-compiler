#include "annotation_visitor.hpp"

bool AnnotationVisitor::VisitIfStmt(IfStmt* stmt) {
  annotations_->push_back(Annotation("if"));

  llvm::errs() << "MATCH";
  return true;
}
