#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

// std::mutex mtx;
// std::condition_variable cv;
// bool ready = false;  // 标记变量，指示打印数字的线程是否可以开始工作
// bool printed = false;  // 标记变量，指示字母是否已经打印

// void printChar() {
//   std::unique_lock<std::mutex> lock(mtx);
//   for (char c = 'A'; c <= 'D'; ++c) {
//     std::cout << c;   // 打印字母
//     ready = true;     // 设置标记为true，表示数字可以打印
//     printed = true;   // 设置已打印标记
//     cv.notify_one();  // 通知打印数字的线程
//     cv.wait(lock, [] { return !printed; });  // 等待数字打印
//   }
// }

// void printNumber() {
//   std::unique_lock<std::mutex> lock(mtx);
//   for (int i = 1; i <= 4; ++i) {
//     cv.wait(lock, [] { return ready; });  // 等待字母打印
//     std::cout << i;                       // 打印数字
//     ready = false;                        // 重置标记
//     printed = false;                      // 重置已打印标记
//     cv.notify_one();                      // 通知打印字母的线程
//   }
// }

std::mutex mutex;
std::condition_variable condition;
bool print = false;
bool ready = false;

void printChar() {
  std::unique_lock<std::mutex> lock(mutex);
  for (char c = 'A'; c <= 'D'; c++) {
    std::cout << c;
    ready = true;
    print = true;
    condition.notify_all();
    condition.wait(lock, []() { return !print; });
  }
}

void printNumber() {
  std::unique_lock<std::mutex> lock(mutex);
  for (int i = 1; i <= 4; i++) {
    condition.wait(lock, []() { return ready; });
    std::cout << i;
    ready = false;
    print = false;
    condition.notify_all();
  }
}

int main() {
  std::thread t1(printChar);
  std::thread t2(printNumber);

  t1.join();
  t2.join();

  std::cout << std::endl;

  return 0;
}