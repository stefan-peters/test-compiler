#include "annotation_visitor.hpp"
#include <clang/Lex/Preprocessor.h>

namespace {

Position getPosition(const SourceManager& sm, const SourceLocation& loc) {
  Position pos;
  pos.line = sm.getSpellingLineNumber(loc) - 1;
  pos.column = sm.getSpellingColumnNumber(loc) - 1;
  return pos;
}

Range getRange(const ASTContext* context, const Stmt* stmt) {
  auto& sm = context->getSourceManager();
  auto start_loc = stmt->getLocStart();
  auto end_loc = stmt->getLocEnd();

  // macros need a special handling, because we are interessted in the macro
  // instanciation location and not in the macro definition location
  if (start_loc.isMacroID()) {
    start_loc = sm.getImmediateExpansionRange(start_loc).first;
  }

  Range r;

  r.start = getPosition(
      sm, Lexer::GetBeginningOfToken(start_loc, sm, context->getLangOpts()));
  r.end = getPosition(
      sm, Lexer::getLocForEndOfToken(end_loc, 0, sm, context->getLangOpts()));
  return r;
}

template <class T>
Annotation createBranchAnnotation(const ASTContext* context, T stmt,
                                  const char* name) {
  auto a = Annotation{name};

  if (stmt->getConditionVariableDeclStmt()) {
    a.visual = getRange(context, stmt->getConditionVariableDeclStmt());
  } else if (stmt->getCond()) {
    a.visual = getRange(context, stmt->getCond());
  }

  a.marker = a.visual;
  return a;
}

inline bool isInsideMainFile(ASTContext* context, Stmt* stmt) {
  return context->getSourceManager().isInMainFile(stmt->getLocStart());
}
}

bool AnnotationVisitor::VisitIfStmt(IfStmt* stmt) {
  if (isInsideMainFile(context_, stmt)) {
    auto annotation = createBranchAnnotation(context_, stmt, "if");
    if (isValid(annotation)) {
      annotations_->push_back(annotation);
    }
  }

  return true;
}

bool AnnotationVisitor::VisitForStmt(ForStmt* stmt) {
  if (isInsideMainFile(context_, stmt)) {
    auto annotation = createBranchAnnotation(context_, stmt, "for");
    if (isValid(annotation)) {
      annotations_->push_back(annotation);
    }
  }

  return true;
}

bool AnnotationVisitor::VisitWhileStmt(WhileStmt* stmt) {
  if (isInsideMainFile(context_, stmt)) {
    auto annotation = createBranchAnnotation(context_, stmt, "while");
    if (
      isValid(annotation)) { annotations_->push_back(annotation); }
  }

  return true;
}
