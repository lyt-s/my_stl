#include "foo.h"
#include "stdint.h"
#include "stdio.h"

inline int32_t i = 3;
// extern int32_t i;  // 1. --> foo.cpp

// int32_t i;

#include <iostream>
#include <memory>

#include "a.h"

struct S {
  int x;
  float y;
  double z;

  S(int x, float y, double z) : x{x}, y{y}, z{z} { std::cout << "S::S();\n"; }

  ~S() { std::cout << "S::~S();\n"; }

  void print() const {
    std::cout << "S { x=" << x << "; y=" << y << "; z=" << z << "; };\n";
  }
};

void function() {
  static int count = 0;  // count 在这里初始化一次，且之后不会被重置。
  count++;
  printf("%d\n", count);
}

int main() {
  print();
  int z = 0;
  auto i = z;
  int&& a = 3;
  int* p = &a;
  printf("p : %p\n", p);
  auto&& b = 6;
  int* p2 = &b;
  printf("p2 : %p\n", p2);
  alignas(S) unsigned char storage[sizeof(S)];
  S* ptr =
      std::construct_at(reinterpret_cast<S*>(storage), 42, 2.71828f, 3.1415);
  ptr->print();

  std::destroy_at(ptr);

  function();
  function();

  // test inline
  printf("main 里看到的 twice = %p!\n", twice);
  printf("twice(3) = %d!\n", twice(3));
  printf("main %d!\n", i);
  foo();
  foo();
  foo();
  printf("main %d!\n", i);
  return 0;
}