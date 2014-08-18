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

#include <cmc/parser.h>
#include <algorithm>

// // Apply a custom category to all command-line options so that they are the
// // only ones displayed.
// static llvm::cl::OptionCategory MyToolCategory("my-tool options");

// // CommonOptionsParser declares HelpMessage with a description of the common
// // command-line options related to the compilation database and input files.
// // It's nice to have this help message in all tools.
// static cl::extrahelp CommonHelp(CommonOptionsParser::HelpMessage);

// // A help message for this specific tool can be added afterwards.
// static cl::extrahelp MoreHelp("\nMore help text...");

// int main(int argc, const char **argv) {

// CommonOptionsParser OptionsParser(argc, argv, MyToolCategory);
// ClangTool Tool(OptionsParser.getCompilations(),
//                OptionsParser.getSourcePathList());
// return Tool.run(newFrontendActionFactory<clang::SyntaxOnlyAction>().get());

std::list<cmc::Enum> values;
 
class FindNamedClassVisitor
    : public RecursiveASTVisitor<FindNamedClassVisitor> {
public:
  explicit FindNamedClassVisitor(ASTContext *Context) : Context(Context) {}

  bool VisitEnumDecl(EnumDecl *ED) {

    auto ed = ED->getDefinition();

    if (ed) {
      cmc::Enum e;

      if(ed->getTypedefNameForAnonDecl()) {
        e.name = ed->getTypedefNameForAnonDecl()->getName();
      }
      else {
        e.name = ed->getName();
      }
      values.push_back(e);
    }
    return true;
  }

  bool VisitEnumConstantDecl(EnumConstantDecl *ECD) {
    auto v = std::make_tuple<std::string, int>( 
        ECD->getName(), ECD->getInitVal().getSExtValue());
    values.back().values.push_back(v);
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


namespace cmc {

std::list<cmc::Enum> parseCode(const std::string &code,
                               const std::vector<std::string> &args) {
  values.clear();
  
  runToolOnCodeWithArgs(new FindNamedClassAction, code, args);
  std::sort(values.back().values.begin(), values.back().values.end(), std::greater<cmc::Enum::Value>());

  return values;
}
}