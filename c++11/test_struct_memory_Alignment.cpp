#include <stdio.h>
struct A {
  char c1;
  char c2;
  int i;
  double d;
};
struct B {
  char c1;
  int i;
  char c2;
  double d;
};

struct Test01 {
  char c;
  short s;
  int i;
  double d;
} t1;

struct Test02 {
  char c;
  double d;
  int i;
  short s;
} t2;

struct Test03 {
  // 24
  short s;
  double d;
  char c;
  int i;
} t3;
struct Test04 {
  // 24
  double d;
  char c;
  int i;
  short s;
} t4;

void showTest01() {
  printf("Test01所占内存大小：%ld\n", sizeof(Test01));
  // 并按照声明顺序输出 Test01 中的成员变量地址对应的十六进制
  printf("%p\n", &t1.c);
  printf("%p\n", &t1.s);
  printf("%p\n", &t1.i);
  printf("%p\n", &t1.d);
}

void showTest02() {
  printf("Test01所占内存大小：%ld\n", sizeof(Test02));
  // 并按照声明顺序输出 Test01 中的成员变量地址对应的十六进制
  printf("%p\n", &t2.c);
  printf("%p\n", &t2.s);
  printf("%p\n", &t2.i);
  printf("%p\n", &t2.d);
}

void showTest03() {
  printf("Test01所占内存大小：%ld\n", sizeof(Test03));
  // 并按照声明顺序输出 Test01 中的成员变量地址对应的十六进制
  printf("%p\n", &t3.c);
  printf("%p\n", &t3.s);
  printf("%p\n", &t3.i);
  printf("%p\n", &t3.d);
}
void showTest04() {
  printf("Test01所占内存大小：%ld\n", sizeof(Test04));
  // 并按照声明顺序输出 Test01 中的成员变量地址对应的十六进制
  printf("%p\n", &t4.c);
  printf("%p\n", &t4.s);
  printf("%p\n", &t4.i);
  printf("%p\n", &t4.d);
}
int main() {
  printf("结构体A所占内存大小为：%ld\n", sizeof(A));
  printf("结构体B所占内存大小为：%ld\n", sizeof(B));

  showTest01();

  showTest02();

  showTest03();
  showTest04();
  return 0;
}