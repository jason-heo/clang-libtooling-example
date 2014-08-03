LIB = -fno-rtti \
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
    -lclangBasic  -lLLVMSupport -I~/opt/include/ -lpthread


all: ex01 ex02 ex03 ex04

ex01: ex01.cc
	g++ -o ex01 ex01.cc -g $(LIB) \
    `llvm-config --cxxflags --ldflags --libs all --system-libs`

ex02: ex02.cc
	g++ -o ex02 ex02.cc -g $(LIB) \
    `llvm-config --cxxflags --ldflags --libs all --system-libs`

ex03: ex03.cc
	g++ -o ex03 ex03.cc -g $(LIB) \
    `llvm-config --cxxflags --ldflags --libs all --system-libs`

ex04: ex04.cc
	g++ -o ex04 ex04.cc -g $(LIB) \
    `llvm-config --cxxflags --ldflags --libs all --system-libs`

clean:
	rm -f core ex01 ex02 ex03 ex04
