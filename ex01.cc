#include "clang/Driver/Options.h"
#include "clang/AST/AST.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/ASTConsumers.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Rewrite/Core/Rewriter.h"

using namespace std;
using namespace llvm;

clang::Rewriter rewriter;
int numFunctions = 0;


class ExampleVisitor : public clang::RecursiveASTVisitor<ExampleVisitor>
{
private:
    clang::ASTContext* ast_context_; // used for getting additional AST info

public:
    explicit ExampleVisitor(clang::CompilerInstance* ci) 
      : ast_context_(&(ci->getASTContext())) // initialize private members
    {
        rewriter.setSourceMgr(ast_context_->getSourceManager(),
                ast_context_->getLangOpts());
    }

    virtual bool VisitFunctionDecl(clang::FunctionDecl* func)
    {
        numFunctions++;

        string funcName = func->getNameInfo().getName().getAsString();
        if (funcName == "do_math")
        {
            rewriter.ReplaceText(func->getLocation(), funcName.length(),"add5");
            errs() << "** Rewrote function def: " << funcName << "\n";
        }    
        return true;
    }

    virtual bool VisitStmt(clang::Stmt* st)
    {
        if (clang::ReturnStmt *ret = dyn_cast<clang::ReturnStmt>(st))
        {
            rewriter.ReplaceText(ret->getRetValue()->getLocStart(), 6, "val");
            errs() << "** Rewrote ReturnStmt\n";
        }        
        if (clang::CallExpr* call = dyn_cast<clang::CallExpr>(st))
        {
            rewriter.ReplaceText(call->getLocStart(), 7, "add5");
            errs() << "** Rewrote function call\n";
        }
        return true;
    }

/*
    virtual bool VisitReturnStmt(clang::ReturnStmt* ret) {
        rewriter.ReplaceText(ret->getRetValue()->getLocStart(), 6, "val");
        errs() << "** Rewrote ReturnStmt\n";
        return true;
    }

    virtual bool VisitCallExpr(clang::CallExpr* call) {
        rewriter.ReplaceText(call->getLocStart(), 7, "add5");
        errs() << "** Rewrote function call\n";
        return true;
    }
*/
};


class ExampleASTConsumer : public clang::ASTConsumer
{
private:
    ExampleVisitor* visitor_; // doesn't have to be private

public:
    // override the constructor in order to pass CI
    explicit ExampleASTConsumer(clang::CompilerInstance* ci)
        : visitor_(new ExampleVisitor(ci)) // initialize the visitor_
    {
    }

    // override this to call our ExampleVisitor on the entire source file
    virtual void HandleTranslationUnit(clang::ASTContext& context)
    {
        /**
         * we can use ASTContext to get the TranslationUnitDecl, which is
           a single Decl that collectively represents the entire source file 
         */

        visitor_->TraverseDecl(context.getTranslationUnitDecl());
    }

    /*
    // override this to call our ExampleVisitor on each top-level Decl
    virtual bool HandleTopLevelDecl(clang::DeclGroupRef DG)
    {
        // a DeclGroupRef may have multiple Decls, so we iterate through each one
        for (clang::DeclGroupRef::iterator i = DG.begin(), e = DG.end();
             i != e; i++)
        {
            Decl *D = *i;    
            visitor_->TraverseDecl(D); // recursively visit each AST node
                                      // in Decl "D"
        }
        return true;
    }
    */
};

class ExampleFrontendAction : public clang::ASTFrontendAction
{
public:
    virtual clang::ASTConsumer* CreateASTConsumer(clang::CompilerInstance& ci,
                                                  llvm::StringRef file)
    {
        return new ExampleASTConsumer(&ci); // pass CI pointer to ASTConsumer
    }
};


int main(int argc, const char **argv)
{
    // parse the command-line args passed to your code
    cl::OptionCategory my_tool_category("my tool option");
    clang::tooling::CommonOptionsParser op(argc, argv, my_tool_category);
    
    // create a new Clang Tool instance (a LibTooling environment)
    clang::tooling::ClangTool tool(op.getCompilations(),op.getSourcePathList());

    // run the Clang Tool, creating a new FrontendAction (explained below)
    int result = tool.run(
        clang::tooling::newFrontendActionFactory<ExampleFrontendAction>().get()
    );

    errs() << "\nFound " << numFunctions << " functions.\n\n";

    // print out the rewritten source code ("rewriter" is a global var.)
    rewriter.getEditBuffer(
        rewriter.getSourceMgr().getMainFileID()).write(errs());

    return result;
}
