# 소개 (Intro.)

본 예제들은 본인이 Clang을 공부하면서 찾은 자료들을 1) Clang 3.5에서 컴파일 되도록 수정한 예제들과 2) 직접 만들어본 예제들입니다. Clang을 처음 접했을 때 관련 자료를 찾기 어려웠는데 본 예제들이 Clang을 처음 접하는 개발자들에게 도움이 되었으면 합니다.

Those examples are not only collected and modified by me, so that compiled on Clang 3.5 but also made by myself to test own my project. I hope those examples might help Clang newbie (like me).

# 파일 구조 (Structure)

`ex-`로 시작하는 파일들이 있습니다. 예를 들어,

- `ex01.cc` : 메인 프로그램
- `ex01-input.cc` : `ex01`에 의해 분석될 입력 파일입니다.
- `ex01-run.sh` : `ex01`을 실행하는 쉘 스크립트이다.

There are `ex-` prefixed files. for examples,

- `ex01.cc` : main program
- `ex01-input.cc` : source file to be analyzed by `ex01`
- `ex01-run.sh` : shell script for invoking `ex01`

# ex01

본 예제는 [Clang LibTooling Example][1] 를 g++ 4.8.2, clang 3.5에서 작동하도록 수정한 버전입니다.

This git project is ported version of [Clang LibTooling Example][1] for g++ 4.8.2 and clang 3.5. Original example does not complied with clang 3.5. that's why I made some changes.

# ex02

Clang 공식 홈페이지에 있는 [ASTMatcher 튜토리얼][2]을 컴파일 및 링킹이 되도록 테스트한 프로그램입니다. 튜토리얼에 Makefile이 없어서 어떻게 컴파일할지 모르는 경우 도움이 될 것입니다.

This example provides `Makefile` for showing how to compile and linking [ASTMatcher Tutorial][2].

# ex03

ex03보다 좀 더 복잡한 ASTMatcher 예입니다. 본인의 목적에 의해서 개발되었으며, 생성자에서 멤버 변수 초기화하는 코드에 접근하는 예입니다.

`ex03` is (at least to me) more complex ASTMatcher example which access constructor member initializer.

# ex04

Stackoverflow에 올라온 질문의 답이 되는 소스입니다. 저도 [ASTMatcher 메뉴얼][4]을 보면서 공부해가는 처지라 속도는 느리지만 도움이 될까 하고 작성해 보았습니다.

This is a code for Question posted in [Stackoverflow][3] and shows how to get type of `VarDecl` and get Class name of `FieldDecl` belong to.

[1]: http://kevinaboos.wordpress.com/2013/07/23/clang-tutorial-part-ii-libtooling-example/
[2]: http://clang.llvm.org/docs/LibASTMatchersTutorial.html
[3]: http://stackoverflow.com/questions/20719834/clang-libtooling-fetching-datatype-of-a-variable-inside-clangvardecl-clang 
[4]: http://clang.llvm.org/docs/LibASTMatchersReference.html
