#include <cstdio>
#include <iostream>

int main() {
  unsigned long a = 0x4869576f;

  printf("a : %s\n", (char*)&a);
  return 0;
}