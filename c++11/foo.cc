#include "foo.h"

#include <cstdint>
#include <cstdio>
#include <iostream>

// inline int32_t i = 0;

// int i = 3;  // 1.
void foo() {
  std::cout << "foo " << i++ << "!"
            << "\n";
  printf("foo 里看到的 twice = %p!\n", twice);
}