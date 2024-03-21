#include <cstdio>
#include <iostream>
using namespace std;
// 第⼀种：gcc扩展，标记这个函数应当在main函数之前执⾏。同样有⼀个__attribute((destructor))，标记函
// 数应当在程序结束之前（main结束之后，或者调⽤了exit后）执⾏;
__attribute((constructor)) void before() { printf("before main 1\n"); }

// 第⼆种：全局 static 变量的初始化在程序初始阶段，先于 main 函数的执⾏
int test1() {
  cout << "before main 2" << endl;
  return 1;
}
static int i = test1();
// 第三种：知乎⼤⽜ Milo Yip 的回答利⽤ lambda 表达式
int a = []() {
  cout << "before main 3" << endl;
  return 0;
}();

int b = []() {
  cout << "before main 4" << endl;
  return 0;
}();

int main(int argc, char** argv) {
  cout << "main function" << endl;
  return 0;
}