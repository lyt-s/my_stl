#include <stdio.h>
#include <unistd.h>
int main(int argc, char* argv[]) {
  fork();
  fork() && fork() || fork();
  fork();
  int count = 0;
  printf("+\n");
}