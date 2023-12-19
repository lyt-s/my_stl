#include <cstddef>
#include <deque>
#include <iostream>
#include <memory>

class MyClass {
 public:
  MyClass() : m_data(nullptr) {}
  ~MyClass() { delete[] m_data; }

  MyClass(MyClass &&other) noexcept {
    std::cout << "Moving MyClass" << std::endl;
    m_data = other.m_data;
    other.m_data = nullptr;
  }

  //   MyClass &operator=(MyClass &&other) noexcept {
  //     std::cout << "Moving Operator=" << std::endl;
  //     if (this != &other) {
  //       delete m_data;
  //       m_data = other.m_data;
  //       other.m_data = nullptr;
  //     }
  //     return *this;
  //   }

 private:
  int *m_data;
  size_t m_size;
};

int main() {
  MyClass t1;
  MyClass t2;

  MyClass t3(std::forward<MyClass>(t1));
  MyClass t4 = std::forward<MyClass>(t2);

  return 0;
}
