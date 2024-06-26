
#include <condition_variable>
// #include <format>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <stack>
#include <thread>
#include <vector>
// std::stack<int> q; //
std::queue<int> q;

std::mutex mutex;
std::condition_variable cv;

int pop_gift() {
  std::unique_lock lk(mutex);
  cv.wait(lk, [] { return !q.empty(); });
  auto gift = q.front();
  if (gift != 0) {
    q.pop();
  }
  return gift;
}

void push_gift(int i) {
  std::unique_lock lk(mutex);
  q.push(i);
  lk.unlock();
  cv.notify_one();
}

void producer() {
  for (int i = 1; i < 100; i++) {
    push_gift(i);
  }
  push_gift(0);
}

void consumer(int id) {
  while (int gift = pop_gift()) {
    // std::cout << std::format("小朋友 { } 得到了 {}", id, gift);
  }
}

int main() {
  std::jthread producer1_thread(producer);
  std::vector<std::jthread> consumer_threads;
  for (int i = 0; i < 32; i++) {
    std::jthread consumer_thread(consumer, i);
    consumer_threads.push_back(std::move(consumer_thread));
  }
  producer1_thread.detach();
  return 0;
}