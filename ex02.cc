#include <iostream>

// Declares clang::SyntaxOnlyAction.
#include "clang/Frontend/FrontendActions.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"

// Declares llvm::cl::extrahelp.
#include "llvm/Support/CommandLine.h"

#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::tooling;
using namespace llvm;

using namespace clang;
using namespace clang::ast_matchers;

StatementMatcher LoopMatcher0 =
  forStmt(hasLoopInit(declStmt(hasSingleDecl(varDecl(
    hasInitializer(integerLiteral(equals(0)))))))).bind("forLoop0");

StatementMatcher LoopMatcher1 =
  forStmt(hasLoopInit(declStmt(hasSingleDecl(varDecl(
    hasInitializer(integerLiteral(equals(1)))))))).bind("forLoop1");

class LoopPrinter : public MatchFinder::MatchCallback
{
public :
    virtual void run(const MatchFinder::MatchResult &Result)
    {
        if (const ForStmt *FS
            = Result.Nodes.getNodeAs<clang::ForStmt>("forLoop0"))
        {
            std::cout << "===== found: forLoop0 =====" << std::endl;
            FS->dump();
            std::cout << std::endl;
        }
        else if (const ForStmt *FS
            = Result.Nodes.getNodeAs<clang::ForStmt>("forLoop1"))
        {
            std::cout << "===== found: forLoop1 =====" << std::endl;
            std::cout << "do nothing" << std::endl << std::endl;
        }
    }
};

// Apply a custom category to all command-line options so that they are the
// only ones displayed.
static llvm::cl::OptionCategory MyToolCategory("my-tool options");

// CommonOptionsParser declares HelpMessage with a description of the common
// command-line options related to the compilation database and input files.
// It's nice to have this help message in all tools.
static cl::extrahelp CommonHelp(CommonOptionsParser::HelpMessage);

// A help message for this specific tool can be added afterwards.
static cl::extrahelp MoreHelp("\nMore help text...");

int main(int argc, const char **argv)
{
    CommonOptionsParser OptionsParser(argc, argv, MyToolCategory);
    ClangTool Tool(OptionsParser.getCompilations(),
                   OptionsParser.getSourcePathList());

    LoopPrinter printer;
    clang::ast_matchers::MatchFinder finder;
    finder.addMatcher(LoopMatcher0, &printer);
    finder.addMatcher(LoopMatcher1, &printer);

    return Tool.run(newFrontendActionFactory(&finder).get());
}
