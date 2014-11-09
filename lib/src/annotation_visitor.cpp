#include "annotation_visitor.hpp"

bool AnnotationVisitor::VisitIfStmt(IfStmt* stmt) {
  llvm::errs() << "MATCH";
  return true;
}
