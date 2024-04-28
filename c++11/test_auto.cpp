#include <iostream>
#include <vector>

template <typename T>  // 带有与x的声明等价的
void f(T param);       // 形参声明的模板

int main() {
  std::vector<bool> flag(10, 1);

  auto f = flag[5];

  bool k = flag[5];
  // auto x5 = {1, 2, 3.0};  // 错误！无法推导std::initializer_list<T>中的T
  auto x = {11, 23, 9};  // x的类型是std::initializer_list<int>

  // f({11, 23, 9});  // 错误！不能推导出T
  return 0;
}