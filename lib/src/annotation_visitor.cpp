#include "annotation_visitor.hpp"
#include <clang/Lex/Preprocessor.h>

Annotation createAnnotation(const std::string& name, Stmt* stmt) {
  Annotation a;
  a.name = name;

  return a;
}

bool AnnotationVisitor::VisitIfStmt(IfStmt* stmt) {
  auto a = createAnnotation("if", stmt);
  a.visual = getRange(stmt->getCond());
  // a.marker = getRange(stmt->getCond());
  annotations_->push_back(a);

  return true;
}

Position AnnotationVisitor::getPosition(const SourceLocation& loc) const {
  Position pos;
  pos.line = context_->getSourceManager().getSpellingLineNumber(loc) - 1;
  pos.column = context_->getSourceManager().getSpellingColumnNumber(loc) - 1;
  return pos;
}

Range AnnotationVisitor::getRange(Stmt* stmt) const {
  Range r;
  r.start = getPosition(Lexer::GetBeginningOfToken(stmt->getLocStart(),
                                                   context_->getSourceManager(),
                                                   context_->getLangOpts()));
  r.end = getPosition(Lexer::getLocForEndOfToken(stmt->getLocEnd(), 0,
                                                 context_->getSourceManager(),
                                                 context_->getLangOpts()));
  return r;
}
