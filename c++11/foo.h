#pragma once
#include <cstdint>
#include <cstdio>
#include <string>

// inline int32_t i = 0;

// extern int32_t i;
// static 和 inline 的区别  todo  总结
// static int twice(int x) { return x * 2; };
// 这里和内联优化没有任何关系

inline int twice(int x) { return x * 2; };
void foo();

struct Foo {
 private:
  std::string zyf;

 public:
  void print() const { printf("my name is %s\n", zyf.c_str()); }
};
