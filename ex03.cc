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

DeclarationMatcher AccessSpecMatcher =
    clang::ast_matchers::accessSpecDecl().bind("access_spec");

StatementMatcher MemberExprMatcher =
    clang::ast_matchers::memberExpr().bind("member_expr");

DeclarationMatcher CtorInitMatcher =
    clang::ast_matchers::constructorDecl(forEachConstructorInitializer(ctorInitializer())).bind("ctor_init");

clang::Rewriter rewriter;

class LoopPrinter : public MatchFinder::MatchCallback
{
public :
    virtual void run(const MatchFinder::MatchResult& result)
    {
        std::cout << "run()..." << std::endl;

        clang::ASTContext* context = result.Context;
        if (const clang::AccessSpecDecl* fs
            = result.Nodes.getNodeAs<clang::AccessSpecDecl>("access_spec"))
        {
            std::cout << "===== found: AccessSpec =====" << std::endl;
            fs->dump();
            std::cout << std::endl;
        }

        if (const clang::MemberExpr* fs
            = result.Nodes.getNodeAs<clang::MemberExpr>("member_expr"))
        {
            std::cout << "===== found: MemberExpr =====" << std::endl;
            fs->dump();
            std::cout << std::endl;
        }

        if (const clang::CXXConstructorDecl* fs
            = result.Nodes.getNodeAs<clang::CXXConstructorDecl>("ctor_init"))
        {
            std::cout << "===== found: CtorInit =====" << std::endl;
            //fs->dump();
            std::cout << fs->getNameInfo().getName().getAsString() << std::endl;
            std::cout << fs->getNumCtorInitializers() << std::endl;

            for (clang::CXXConstructorDecl::init_const_iterator its
                 = fs->init_begin(), ite = fs->init_end()
                 ; its != ite; ++its)
            {
                const clang::CXXCtorInitializer* ctor_init = *its;
                const clang::FieldDecl* field = ctor_init->getMember();
                std::cout << field->getName().str()
                          << std::endl;

            }

            std::cout << std::endl;
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
    //finder.addMatcher(AccessSpecMatcher, &printer);
    //finder.addMatcher(MemberExprMatcher, &printer);
    finder.addMatcher(CtorInitMatcher, &printer);

    return Tool.run(newFrontendActionFactory(&finder).get());
}
