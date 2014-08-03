#include <iostream>

// Declares clang::SyntaxOnlyAction.
#include "clang/Frontend/FrontendActions.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"

// Declares llvm::cl::extrahelp.
#include "llvm/Support/CommandLine.h"

#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

#include "clang/Rewrite/Core/Rewriter.h"

using namespace clang::tooling;
using namespace llvm;

using namespace clang;
using namespace clang::ast_matchers;

DeclarationMatcher FieldDeclMatcher =
    clang::ast_matchers::fieldDecl().bind("field_decl");


class LoopPrinter : public MatchFinder::MatchCallback
{
public :
    virtual void run(const MatchFinder::MatchResult& result)
    {
        if (const clang::FieldDecl* fd
            = result.Nodes.getNodeAs<clang::FieldDecl>("field_decl"))
        {
            std::cout << "======== FieldDecl found ======" << std::endl;

            const clang::RecordDecl* rd = fd->getParent();
            const clang::QualType qt = fd->getType();
            const clang::Type* t = qt.getTypePtr();
            
            std::cout << "FieldDecl found '"
                      << fd->getQualifiedNameAsString() << " "
                      << fd->getName().str() << "' in '"
                      << rd->getName().str() << "'. "
                      << "is Builtintype = " << t->isBuiltinType() << " "
                      << std::endl << std::endl;
        }

    } // end of run()
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
    finder.addMatcher(FieldDeclMatcher, &printer);

    return Tool.run(newFrontendActionFactory(&finder).get());
}
