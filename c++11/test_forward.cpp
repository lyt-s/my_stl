#include <cstddef>
#include <cstdio>
#include <deque>
#include <iostream>
#include <memory>
#include <utility>

class MyClass {
 public:
  MyClass() : m_data(nullptr) {}
  ~MyClass() { delete[] m_data; }

  MyClass(MyClass&& other) noexcept {
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
  int* m_data;
  size_t m_size;
};
void fun_B(int&& x) { printf("右值 x: %d\n", x); }
void fun_B(int& x) { printf("左值 x: %d\n", x); }

void fun(int&& x) {
  // printf("右值  x: %d\n", x);
  // fun_B(x);
  fun_B(std::forward<int&&>(std::move(x)));
}
void fun(int& x) { printf("左值 x: %d\n", x); }

int main() {
  MyClass t1;
  MyClass t2;
  int x = 10;      // 'x' 是左值
  int& lref = x;   // 'lref' 是'x'的左值引用
  int&& rref = 5;  // 'rref' 是字面量5的右值引用

  fun(6);

  lref = 15;          // 通过左值引用修改了'x'
  int& lref2 = rref;  // 错误：不能将左值引用绑定到右值
  MyClass t3(std::forward<MyClass>(t1));
  MyClass t4 = std::forward<MyClass>(t2);
  // t3 = std::forward<MyClass>(t2);

  return 0;
}
