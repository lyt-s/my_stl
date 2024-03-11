// #include <iostream>
// class Parent {
//  public:
//   Parent() { std::cout << "1"; }
//   Parent(const Parent &p) { std::cout << "2"; }
//   const Parent &operator=(const Parent &p) {
//     std::cout << "3";
//     return *this;
//   }
// };
// int main() {
//   Parent p;
//   Parent p1(p);
//   Parent p2 = p;
//   p2 = p1;
// }
#include <iostream>
#include <utility>
class E {
 public:
  virtual void func(int i = 0) { std::cout << "E::func()\t" << i << "\n"; }
};
class F : public E {
 public:
  virtual void func(int i = 1) { std::cout << "F::func()\t" << i << "\n"; }
};

#include <stdio.h>

int inc(int a) { return (++a); }

int multi(int* a, int* b, int* c) { return (*c = *a * *b); }
typedef int (*FUNC1)(int in);
typedef int (*FUNC2)(int*, int*, int*);

void show(FUNC2 fun, int arg1, int* arg2) {
  FUNC1 p = &inc;
  int temp = p(arg1);
  fun(&temp, &arg1, arg2);
  printf(" %d\n", *arg2);
}

int main() {
  int a;
  show(multi, 10, &a);
  int i = 8;
  int j = 9;
  int& x = i;
  i = std::move(j);  // 就是拷贝，因为 int 没有移动构造函数
  std::cout << x << std::endl;
  std::cout << i << std::endl;
  std::cout << j << std::endl;
  return 0;
}

// #include <string.h>

// #include <cstdio>
// #include <cstdlib>

// int main() {
//   char src[] = "hello, world";
//   char* dest = NULL;
//   int len = strlen(src);
//   dest = (char*)malloc(len + 1);  // 分配 len+1 个字节的内存
//   char* d = dest;
//   char* s = src + len - 1;         // 指向 src 的最后一个字符
//   while (len-- != 0) *d++ = *s--;  // 逐个复制字符
//   *d = '\0';                       // 添加结束符
//   printf("%s", dest);
//   free(dest);  // 释放动态分配的内存
//   return 0;
// }
