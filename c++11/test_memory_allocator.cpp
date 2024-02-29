#include <cstring>
#include <iostream>
int a = 0;  // 全局初始化区 .data
char *p;    // 全局未初始化区 .bss

int main() {
  int b;                          // 栈区
  char s[] = "abcd";              // 栈区
  char *p2;                       // 栈区
  char *p3 = "123456";            // 123456在常量区，p3在栈区
  static int c = 0;               // 全局（静态）初始化区 .data
  char *p1 = (char *)malloc(10);  // 分配所得的10字节区域位于堆区
  p2 = (char *)malloc(20);        // 分配所得的20字节区域位于堆区
  strcpy(p1, "123456");
  return 0;
}
