#include <algorithm>
#include <condition_variable>
#include <cstddef>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

using namespace std;

class SingleInstance {
 public:
  static SingleInstance* getInstance() {
    static SingleInstance ins;
    return &ins;
  }

  ~SingleInstance() {}

  static std::mutex m_mutex;

 private:
  SingleInstance() { cout << " single instance created" << endl; }
  SingleInstance(const SingleInstance& other) {}
  SingleInstance& operator=(const SingleInstance& other) { return *this; }
  static SingleInstance* ins;
};

class ThreadPool {
 private:
  bool m_stop;
  std::mutex m_mutex;
  std::condition_variable m_condition;
  vector<std::thread> m_threads;
  std::queue<std::function<void()>> m_taskQueue;

 public:
  ThreadPool(int numThreads) : m_stop(false) {
    for (int i = 0; i < numThreads; ++i) {
      m_threads.emplace_back(std::thread([this]() {
        while (1) {
          unique_lock<std::mutex> lock(m_mutex);
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
      unique_lock<std::mutex> lock(m_mutex);
      m_stop = true;
    }
    m_condition.notify_all();
    for (int i = 0; i < m_threads.size(); ++i) {
      m_threads[i].join();
    }
  }

  template <class F, class... Args>
  void enqueue(F&& f, Args&&... args) {
    auto task = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
    {
      unique_lock<std::mutex> lock(m_mutex);
      m_taskQueue.push(std::move(task));
    }
    m_condition.notify_one();
  }
};

// SingleInstance* SingleInstance::ins = nullptr;
std::mutex SingleInstance::m_mutex;

class Vector {
 private:
  int* m_data;
  std::size_t m_size;
  size_t m_capacity;

 public:
  Vector() : m_data(nullptr), m_size(0), m_capacity(0) {}

  Vector(size_t nums, int value) {
    m_data = new int[nums];
    for (int i = 0; i < nums; ++i) {
      m_data[i] = value;
    }
  }

  Vector(int value) {
    m_data = new int;
    m_data[0] = value;
    m_size = m_capacity = 1;
  }

  Vector(const Vector& other)
      : m_data(other.m_data),
        m_size(other.m_size),
        m_capacity(other.m_capacity) {}

  Vector& operator=(const Vector& other) {
    if (this != &other) {
      delete[] m_data;
      m_data = other.m_data;
      m_size = other.m_size;
      m_capacity = other.m_capacity;
    }
    return *this;
  }

  void reverse(size_t size) {
    if (size <= m_capacity) {
      return;
    }
    int n = std::max(size, m_capacity * 2);
    auto old_data = m_data;
    if (n == 0) {
      m_data = nullptr;
      m_capacity = 0;
    } else {
      m_data = new int[n];
      for (int i = 0; i < m_size; i++) {
        m_data[i] = old_data[i];
      }
      delete[] old_data;
    }
  }

  void push_back(int value) {
    if (m_size + 1 > m_capacity) {
      reverse(m_size + 1);
    }
    m_data[m_size] = value;
    m_size++;
  }

  void pop_back() {
    std::destroy_at(&m_data[m_size - 1]);
    m_size--;
  }

  int* erase(const int* it) {
    int i = it - m_data;
    for (int j = i + 1; j < m_size; j++) {
      m_data[j - 1] = m_data[j];
    }
    std::destroy_at(&m_data[m_size - 1]);
    m_size--;
    return const_cast<int*>(it);
  }
  int* begin() { return m_data; }

  int& operator[](int index) { return m_data[index]; }
  int size() const { return m_size; }
};
int main() {
  Vector vec;
  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);
  vec.erase(vec.begin());
  for (int i = 0; i < vec.size(); i++) {
    cout << vec[i] << " ";
  }
  ThreadPool pool(4);
  for (int i = 0; i < 8; ++i) {
    pool.enqueue([i] {
      std::cout << "Task " << i << " is running in thread "
                << std::this_thread::get_id() << std::endl;
      std::this_thread::sleep_for(std::chrono::seconds(1));
      std::cout << "Task " << i << " is done" << std::endl;
    });
  }
  return 0;
  SingleInstance* ins = SingleInstance::getInstance();

  return 0;
}