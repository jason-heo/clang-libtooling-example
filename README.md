# Clang LibTooling Example

본 예제는 [Clang LibTooling Example][1] 를 g++ 4.8.2, clang 3.5에서 작동하도록 수정한 버전입니다.

This git project is porting of [Clang LibTooling Example][1] for g++ 4.8.2 and clang 3.5. Original example does not complied with clang 3.5. that's why I made some changes.

## Test 환경 (Test Environment)

다음 환경에서 컴파일 및 동작 여부를 확인하였습니다.

I have tested on following environment.

- CentOS 6.3
- g++ 4.8.2
- clang 3.5

## build 및 실행 방법 (How to Build and Run)

### build

	$ git clone https://github.com/mysqlguru/clang-libtooling-example.git example
    $ cd example
    $ make

### 실행 방법 및 그 결과 (running and it's output)
 
    $ ./example input.c --
    ** Rewrote function def: do_math
    ** Rewrote function call
    ** Rewrote ReturnStmt

    Found 2 functions.

    void add5(int *x) {
      *x += 5;
    }

    int main(void) {
      int result = -1, val = 4;
      add5(&val);
      return val;
    }

[1]: http://kevinaboos.wordpress.com/2013/07/23/clang-tutorial-part-ii-libtooling-example/
