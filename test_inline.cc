#include <stdio.h>

#include <cstdint>

#include "foo.h"

// int32_t i = 3;
// extern int32_t i;  // 1. --> foo.cpp

#include <iostream>
#include <memory>

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

int main() {
  alignas(S) unsigned char storage[sizeof(S)];
  S* ptr =
      std::construct_at(reinterpret_cast<S*>(storage), 42, 2.71828f, 3.1415);
  ptr->print();

  std::destroy_at(ptr);

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