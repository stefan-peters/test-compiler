#include "annotation_visitor.hpp"

bool AnnotationVisitor::VisitIfStmt(IfStmt* stmt) {
  Annotation ano;
  ano.name = "if";
  annotations_.push_back(ano);

  llvm::errs() << "MATCH";
  return true;
}
