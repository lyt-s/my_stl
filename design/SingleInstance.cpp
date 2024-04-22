

#include <pthread.h>

#include <iostream>
#include <mutex>
#include <ostream>
#include <string>
#include <thread>

// 饿汉：饿了就饥不择⻝了，所以在单例类定义的时候就进⾏实例化。
// 懒汉：顾名思义，不到万不得已就不会去实例化类，也就是在第⼀次⽤到的类实例的时候才会去实例化。

class SingleInstance {
 public:
  static SingleInstance* getInstance() {
    static SingleInstance ins;
    return &ins;
  }

 private:
  SingleInstance() { std::cout << "SingleInstace 饿汉模式" << std::endl; }
  SingleInstance(const SingleInstance& other) {}
  SingleInstance& operator=(const SingleInstance& other) { return *this; }
};

// 懒汉模式

class SingleInstaceLazy {
 public:
  static SingleInstaceLazy* GetInstance() {
    if (ins == nullptr) {
      // pthread_mutex_lock(&mutex);
      std::call_once(once, init);
      // pthread_mutex_unlock(&mutex);
    }
    return ins;
  }

  static pthread_mutex_t mutex;

  static void init() {
    int i = 0;
    std::cout << i++ << std::endl;
    if (ins == nullptr) {
      ins = new SingleInstaceLazy();
    }
  }

  void PrintLog(std::string msg) {
    std::cout << __TIME__ << ' ' << msg << std::endl;
  }

 private:
  SingleInstaceLazy() {
    std::cout << "SingleInstaceLazy 懒汉模式" << std::endl;
  }
  SingleInstaceLazy(const SingleInstaceLazy& other){};
  SingleInstaceLazy& operator=(const SingleInstaceLazy& other) { return *this; }

  // 静态成员
  static SingleInstaceLazy* ins;
  static std::once_flag once;
};

std::once_flag SingleInstaceLazy::once;
SingleInstaceLazy* SingleInstaceLazy::ins = nullptr;
pthread_mutex_t SingleInstaceLazy::mutex;

void print_error() { SingleInstaceLazy::GetInstance()->PrintLog("error"); }

int main() {
  // 因为不能创建对象所以通过静态成员函数的⽅法返回静态成员变量
  SingleInstance* ins = SingleInstance::getInstance();
  // SingleInstaceLazy* insLazy = SingleInstaceLazy::GetInstance();

  std::thread t1(print_error);
  std::thread t2(print_error);
  t1.join();
  t2.join();
  return 0;
}