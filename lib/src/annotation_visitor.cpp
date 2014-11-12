#include "annotation_visitor.hpp"
#include <clang/Lex/Preprocessor.h>

bool AnnotationVisitor::VisitIfStmt(IfStmt* stmt) {
  auto a = Annotation{"if"};

  if (stmt->getConditionVariableDeclStmt()) {
    a.visual = getRange(stmt->getConditionVariableDeclStmt());
  } else {
    a.visual = getRange(stmt->getCond());
  }

  a.marker = a.visual;

  annotations_->push_back(a);

  return true;
}

Position AnnotationVisitor::getPosition(const SourceLocation& loc) const {

  Position pos;
  pos.line = context_->getSourceManager().getSpellingLineNumber(loc) - 1;
  pos.column = context_->getSourceManager().getSpellingColumnNumber(loc) - 1;
  return pos;
}

Range AnnotationVisitor::getRange(const Stmt* stmt) const {

  SourceLocation start_loc = stmt->getLocStart();
  SourceLocation end_loc = stmt->getLocEnd();

  // macros need a special handling, because we are interessted in the macro
  // instanciation location and not in the macro definition location
  if (start_loc.isMacroID()) {
    start_loc = context_->getSourceManager()
                    .getImmediateExpansionRange(start_loc)
                    .first;
  }

  Range r;

  r.start = getPosition(Lexer::GetBeginningOfToken(
      start_loc, context_->getSourceManager(), context_->getLangOpts()));
  r.end = getPosition(Lexer::getLocForEndOfToken(
      end_loc, 0, context_->getSourceManager(), context_->getLangOpts()));

  return r;
}
