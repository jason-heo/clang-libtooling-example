all: ex01-libtooling ex02-astmatcher

ex01-libtooling: ex01-libtooling.cc
	g++ -o ex01-libtooling ex01-libtooling.cc -g -fno-rtti \
    -lclangFrontend -lclangDriver -lclangTooling \
    -lclangDriver -lclangTooling -lclangFrontendTool \
    -lclangFrontend -lclangDriver -lclangSerialization \
    -lclangCodeGen -lclangParse -lclangSema \
    -lclangStaticAnalyzerFrontend -lclangStaticAnalyzerCheckers \
    -lclangStaticAnalyzerCore -lclangAnalysis \
    -lclangARCMigrate -lclangRewriteFrontend \
    -lclangRewriteCore -lclangEdit  -lclangAST \
    -lclangLex -lclangBasic  -lclangCodeGen -lclangSema \
    -lclangAnalysis  -lclangAST -lclangParse -lclangLex \
    -lclangBasic  -lLLVMSupport -I~/opt/include/ -lpthread \
    `llvm-config --cxxflags --ldflags --libs all --system-libs`

ex02-astmatcher: ex02-astmatcher.cc
	g++ -o ex02-astmatcher ex02-astmatcher.cc -g -fno-rtti \
    -lclangFrontend -lclangDriver -lclangTooling \
    -lclangDriver -lclangTooling -lclangFrontendTool \
    -lclangFrontend -lclangDriver -lclangSerialization \
    -lclangCodeGen -lclangParse -lclangSema \
    -lclangStaticAnalyzerFrontend -lclangStaticAnalyzerCheckers \
    -lclangStaticAnalyzerCore -lclangAnalysis \
    -lclangARCMigrate -lclangRewriteFrontend \
    -lclangRewriteCore -lclangEdit  -lclangAST \
    -lclangLex -lclangBasic  -lclangCodeGen -lclangSema \
    -lclangAnalysis  -lclangAST -lclangParse -lclangLex \
    -lclangASTMatchers \
    -lclangBasic  -lLLVMSupport -I~/opt/include/ -lpthread \
    `llvm-config --cxxflags --ldflags --libs all --system-libs`

clean:
	rm -f core ex01-libtooling ex02-astmatcher
