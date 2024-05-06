

#include <pthread.h>

#include <cstddef>
#include <cstdlib>
#include <iostream>
int num = 0;

void *fun(void *arg) {
  for (int i = 0; i < 10000; i++) {
    num++;
  }
}

int main() {
  // std::thread t1(fun);
  // std::thread t2(fun);

  pthread_t tid;
  pthread_create(&tid, NULL, fun, "线程！！！！");

  int *ptr = (int *)malloc(sizeof(int));

  *ptr = 1;
  free(ptr);
  *ptr = 1;

  return 0;
}

// g++ -g *.cpp  -fsanitize=address
// g++ -g *.cpp  -fsanitize=thread
