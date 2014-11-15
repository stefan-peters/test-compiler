#include "annotation_visitor.hpp"
#include <clang/Lex/Preprocessor.h>
#include <type_traits>

namespace {

Position getPosition(const SourceManager& sm, const SourceLocation& loc) {
  auto pos = Position{};
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

  auto r = Range{};

  r.start = getPosition(
      sm, Lexer::GetBeginningOfToken(start_loc, sm, context->getLangOpts()));
  r.end = getPosition(
      sm, Lexer::getLocForEndOfToken(end_loc, 0, sm, context->getLangOpts()));
  return r;
}

Annotation createBranchAnnotation(const ASTContext* context,
                                  ConditionalOperator* stmt, const char* name) {
  auto a = Annotation{name};

  if (stmt->getCond()) {
    a.visual = getRange(context, stmt->getCond());
  }

  a.marker = a.visual;
  return a;
}

template <class T>
Annotation createBranchAnnotation(const ASTContext* context, T* stmt,
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

template <class T>
bool handleBranchLikeStatement(T* stmt, ASTContext* context,
                               Annotations* annotations, const char* name) {
  if (isInsideMainFile(context, stmt)) {
    auto annotation = createBranchAnnotation(context, stmt, name);
    if (isValid(annotation)) {
      annotations->push_back(annotation);
    }
  }

  return true;
}
}

bool AnnotationVisitor::VisitIfStmt(IfStmt* stmt) {
  return handleBranchLikeStatement(stmt, context_, annotations_, "if");
}

bool AnnotationVisitor::VisitForStmt(ForStmt* stmt) {
  return handleBranchLikeStatement(stmt, context_, annotations_, "for");
}

bool AnnotationVisitor::VisitWhileStmt(WhileStmt* stmt) {
  return handleBranchLikeStatement(stmt, context_, annotations_, "while");
}

bool AnnotationVisitor::VisitConditionalOperator(ConditionalOperator* op) {
  return handleBranchLikeStatement(op, context_, annotations_, "conditional");
}
