
#include <unistd.h>

#include <cstdio>
int main() {
  fork();
  printf("hello world\n");
  fork();
  printf("hello world\n");
  return 0;
}