#include <condition_variable>
#include <cstdint>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <utility>
#include <vector>

class ThreadPool {
 private:
  bool m_stop = false;
  std::mutex m_mutex;
  std::condition_variable m_condition;
  std::vector<std::thread> m_threads;
  std::queue<std::function<void()>> m_taskQueue;

 public:
  ThreadPool(int numThreads) {
    for (int i = 0; i < numThreads; i++) {
      m_threads.push_back(std::thread([this]() {
        while (1) {
          std::unique_lock<std::mutex> lock(m_mutex);
          m_condition.wait(lock,
                           [this]() { return m_stop || !m_taskQueue.empty(); });
          if (m_stop && m_taskQueue.empty()) {
            return;
          }
          auto task = m_taskQueue.front();
          m_taskQueue.pop();
          lock.unlock();
          task();
        }
      }));
    }
  }

  ~ThreadPool() {
    {
      std::unique_lock<std::mutex> lock(m_mutex);
      m_stop = true;
    }
    m_condition.notify_all();
    for (auto &i : m_threads) {
      i.join();
    }
  }

  template <class F, class... Args>
  void enqueue(F &&f, Args &&...args) {
    auto task = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
    {
      std::unique_lock<std::mutex> lock(m_mutex);
      m_taskQueue.push(task);
    }
    m_condition.notify_one();
  }
};

void fun(int num) { std::cout << num << std::endl; }

int main() {
  ThreadPool pool(3);
  pool.enqueue(fun, 9);
}