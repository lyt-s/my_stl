#include "foo.h"

#include <iostream>

// #include "stdint.h"

inline int32_t i;
struct S {
  int x;
  float y;
  double z;
};
// int i = 3;  // 1.
void foo() {
  // std::cout << "foo " << i++ << "!"
  //           << "\n";
  printf("foo 里看到的 twice = %p!\n", twice);
}