
#include <unistd.h>

#include <chrono>
#include <condition_variable>
#include <cstddef>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <utility>
#include <vector>
void print_hello(const std::string& msg) { std::cout << msg << std::endl; }

// 1. 传递临时变量问题
void foo(int& x) { x += 1; }

std::thread t;

void test() {
  int a = 2;
  t = std::thread(foo, std::ref(a));
  std::cout << a << std::endl;
}

class A {
 private:
  friend void thread_foo();
  void foo() { std::cout << "Hello " << std::endl; }
};

void thread_foo() {
  std::shared_ptr<A> a = std::make_shared<A>();
  // 类的成员函数，包含this指针，所以需要传a
  std::thread t(&A::foo, a);

  t.join();
}

int a = 0;
// std::mutex mtx;
std::timed_mutex mtx;
void func() {
  for (int i = 0; i < 2; i++) {
    // mtx.lock();
    // 不支持，隐式转换
    // std::lock_guard<std::mutex> lg(mtx);
    std::unique_lock<std::timed_mutex> lg(mtx, std::defer_lock);
    // 延迟操作
    if (lg.try_lock_for(std::chrono::seconds(5))) {
      std::this_thread::sleep_for(std::chrono::seconds(6));
      a += 1;
    }

    // mtx.unlock();
  }
}

std::mutex mut1;
std::mutex mut2;
// 会出现死锁
void func_1() {
  mut1.lock();
  sleep(1);
  mut2.lock();
  mut2.unlock();
  mut1.unlock();
}

void func_2() {
  mut2.lock();
  mut1.lock();
  mut1.unlock();
  mut2.unlock();
}

class ThreadPool {
 public:
  ThreadPool(int numThreads) : stop(false) {
    for (int i = 0; i < numThreads; i++) {
      m_threads.emplace_back([this]() {
        while (1) {
          std::unique_lock<std::mutex> lock(m_mtx);
          m_condition.wait(lock, [this] { return !m_tasks.empty() || stop; });

          if (stop && m_tasks.empty()) {
            return;
          }
          std::function<void()> task(std::move(m_tasks.front()));
          m_tasks.pop();
          lock.unlock();
          task();
        }
      });
    }
  }

  ~ThreadPool() {
    {
      std::unique_lock<std::mutex> lock(m_mtx);
      stop = true;
    }
    m_condition.notify_all();
    for (auto& t : m_threads) {
      t.join();
    }
  }

  template <class F, class... Args>
  // 函数模板右值引用就是万能引用，引用折叠
  void enqueue(F&& f, Args&&... args) {
    std::function<void()> task =
        std::bind(std::forward<F>(f), std::forward<Args>(args)...);
    {
      std::unique_lock<std::mutex> lock(m_mtx);
      m_tasks.emplace(std::move(task));
    }
    m_condition.notify_one();
  }

 private:
  std::vector<std::thread> m_threads;
  std::queue<std::function<void()>> m_tasks;
  std::mutex m_mtx;
  std::condition_variable m_condition;
  bool stop;
};

void fun(int num) { std::cout << num << std::endl; }

int main() {
  // int a = 1;
  // // 为什么不直接传a, 这里是因为thread构造函数里禁用了隐式类型转换
  // std::thread thread1(foo, std::ref(a));
  // // thread1.join();
  // bool isJoin = thread1.joinable();  // 是否可以调用join
  // if (isJoin) {
  //   thread1.join();
  // }

  // 没报错是因为，test() 在 thread函数执行完成 后 ，结束的。
  // test();
  // t.detach();
  // std::cout << a << std::endl;

  // thread_foo();

  // std::thread t1(func);
  // std::thread t2(func);
  // t1.join();
  // t2.join();
  // std::cout << a << std::endl;

  // std::thread t1(func_1);
  // std::thread t2(func_2);
  // t1.join();
  // t2.join();
  // std::cout << "over" << std::endl;

  // std::thread t3(func);
  // std::thread t4(func);
  // t3.join();
  // t4.join();
  // std::cout << a << std::endl;

  ThreadPool pool(5);
  for (int i = 0; i < 10; i++) {
    // pool.enqueue([i]() {
    //   std::cout << "Task : " << i << "is runing" << std::endl;
    //   std::this_thread::sleep_for(std::chrono::seconds(1));
    // });
    pool.enqueue(fun, i);
  }
  return 0;
}