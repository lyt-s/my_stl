

#include <semaphore.h>

#include <cstdio>
#include <thread>
int v1 = 0, v2 = 0, r1, r2;
sem_t start1, start2, complete;

void thread1() {
  while (true) {
    sem_wait(&start1);
    v1 = 1;
    r1 = v2;

    sem_post(&complete);
  }
}

void thread2() {
  while (true) {
    sem_wait(&start2);
    v2 = 1;
    r2 = v1;

    sem_post(&complete);
  }
}

int main() {
  sem_init(&start1, 0, 0);
  sem_init(&start2, 0, 0);
  sem_init(&complete, 0, 0);

  std::thread t1(thread1);
  std::thread t2(thread2);

  for (int i = 0; i < 300000; i++) {
    v1 = v2 = 0;

    sem_post(&start1);
    sem_post(&start2);

    sem_wait(&complete);
    sem_wait(&complete);

    if ((r1 == 0) && (r2 == 0)) {
      printf("reorder detected @ %d\n", i);
    }
  }
  t1.detach();
  t2.detach();
}