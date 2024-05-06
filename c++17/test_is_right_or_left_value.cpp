#include <iostream>
#include <type_traits>

template <typename T>
void valueCategory(T&&) {
  if constexpr (std::is_lvalue_reference<T>::value) {
    std::cout << "左值" << std::endl;
  } else {
    std::cout << "右值" << std::endl;
  }
}

int main() {
  int x = 5;
  valueCategory(x);  // x是左值
  valueCategory(5);  // 5是右值

  return 0;
}