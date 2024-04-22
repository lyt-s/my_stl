#include <cassert>
#include <cstddef>
#include <iostream>
template <class T>
class SharedPtr {
 private:
  size_t *m_count;
  T *m_ptr;

 public:
  SharedPtr() : m_count(new size_t), m_ptr(nullptr) {}
  SharedPtr(T *ptr) : m_ptr(ptr), m_count(new size_t) { *m_count = 1; }
  SharedPtr(const SharedPtr &other)
      : m_count(other.m_count), m_ptr(other.m_ptr) {
    ++(*m_count);
  }

  SharedPtr &operator=(const SharedPtr &other) {
    if (this == &other) return *this;

    if (m_ptr) {
      --(*m_count);
      if (*m_count == 0) {
        delete m_count;
        delete m_ptr;
      }
    }
    m_ptr = other.m_ptr;
    m_count = other.m_count;
    ++(*m_count);
    return *this;
  }
  ~SharedPtr() {
    --(*m_count);
    if (*m_count == 0) {
      delete m_count;
      delete m_ptr;
      m_ptr = nullptr;
      m_count = nullptr;
    }
  }

  T &operator*() {
    assert(m_ptr != nullptr);
    return *m_ptr;
  }
  T *operator->() {
    assert(m_ptr != nullptr);
    return m_ptr;
  }
  T *get() { return m_ptr; }
  size_t use_count() { return *m_count; }
  bool unique() { return *m_count == 1; }
};

// 简单定义一个使用智能指针管理内存的用户类
class Person {
 public:
  Person(int age, std::string name) : mAge(age), mName(name){};
  std::string info() {
    std::string info = "Name: " + mName + ", Age:" + std::to_string(mAge);
    return info;
  }

 private:
  int mAge;
  std::string mName;
};

int main() {
  SharedPtr<Person> sp1(new Person(10, "zhangsan"));
  SharedPtr<Person> sp2(
      sp1);  // 使用智能指针拷贝构造一个新的智能指针，则 sp2 sp3 引用计数都+1
  SharedPtr<Person> sp3(new Person(20, "Lisi"));

  std::cout << sp1.use_count() << ", " << sp1->info()
            << std::endl;  // 2, Name: zhangsan, Age:10
  std::cout << sp2.use_count() << ", " << sp2->info()
            << std::endl;  // 2, Name: zhangsan, Age:10
  std::cout << sp3.use_count() << ", " << sp3->info()
            << std::endl;  // 1, Name: Lisi, Age:20

  sp2 =
      sp3;  // 使用智能赋值一个智能指针，被赋值的智能sp2原来对应的指针的引用计数-1，用于赋值的智能指针引用计数+1

  std::cout << sp1.use_count() << ", " << sp1->info()
            << std::endl;  // 1, Name: zhangsan, Age:10
  std::cout << sp2.use_count() << ", " << sp2->info()
            << std::endl;  // 2, Name: Lisi, Age:20
  std::cout << sp3.use_count() << ", " << sp3->info()
            << std::endl;  // 2, Name: Lisi, Age:20

  return 0;
}
