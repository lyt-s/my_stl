#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

std::atomic<int> i = 0;

int j = 0;
void test() {
  int num = 10000;
  for (int n = 0; n < num; n++) {
    i++;
    j++;
  }
}

int main() {
  std::vector<bool> a{1, 1, 1, 0, 0, 0};

  for (bool const &i : a) {
    // std::cout << i << std::endl;
  }

  std::vector<int> vec{1, 1, 1};

  for (auto &i : vec) {
    i++;
    std::cout << i;
  }
  std::cout << "\n";
  std::cout << "auto i : vec 处理后" << std::endl;
  for (int i = 0; i < vec.size(); ++i) {
    std::cout << vec[i];
  }

  std::cout << "--------------------------------" << std::endl;
  std::cout << "Starting all threads." << std::endl;

  // create
  std::thread thread_test1(test);
  std::thread thread_test2(test);

  thread_test1.join();
  thread_test2.join();
  std::cout << "All threads joined." << std::endl;

  std::cout << "now i is " << i << std::endl;
  std::cout << "now j is " << j << std::endl;
  return 0;
}