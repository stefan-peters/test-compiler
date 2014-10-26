// Declares clang::SyntaxOnlyAction.
#include "clang/Frontend/FrontendActions.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendAction.h"
#include <clang/AST/ASTContext.h>

// Declares llvm::cl::extrahelp.
#include "llvm/Support/CommandLine.h" 

using namespace clang::tooling;
using namespace llvm;
using namespace clang;

#include <coverage/instrument.h>
#include <algorithm>
 
class FindNamedClassVisitor
    : public RecursiveASTVisitor<FindNamedClassVisitor> {
public:
  explicit FindNamedClassVisitor(ASTContext *Context) : Context(Context) {}

  bool VisitEnumDecl(EnumDecl *ED) {

    // auto ed = ED->getDefinition();

    // if (ed) {
    //   cmc::Enum e;

    //   if(ed->getTypedefNameForAnonDecl()) {
    //     e.name = ed->getTypedefNameForAnonDecl()->getQualifiedNameAsString();
    //   }
    //   else if (not ed->getName().empty()) {
    //     e.name = ed->getQualifiedNameAsString();
    //   }
    //   values.push_back(e);
    // }
    return true;
  }

  bool VisitEnumConstantDecl(EnumConstantDecl *ECD) {
    auto v = std::make_tuple<std::string, int>( 
        ECD->getName(), ECD->getInitVal().getSExtValue());
    //values.back().values.push_back(v);
    return true;
  }

  bool VisitTypedefNameDecl(TypedefNameDecl *TND) {
    return true;
  }

private:
  ASTContext *Context;
};


class FindNamedClassConsumer : public clang::ASTConsumer {
public:
  explicit FindNamedClassConsumer(ASTContext *Context) : Visitor(Context) {}

  virtual void HandleTranslationUnit(clang::ASTContext &Context) {
    Visitor.TraverseDecl(Context.getTranslationUnitDecl());
  }

private:
  FindNamedClassVisitor Visitor;
};


class FindNamedClassAction : public clang::ASTFrontendAction {
public:
  virtual clang::ASTConsumer *
  CreateASTConsumer(clang::CompilerInstance &Compiler, llvm::StringRef InFile) {
    return new FindNamedClassConsumer(&Compiler.getASTContext());
  }
};


namespace coverage {

  std::string instrument(const std::string& code, const ParameterList& args) {
  
    runToolOnCodeWithArgs(new FindNamedClassAction, code, args);
    return code;
  }
}