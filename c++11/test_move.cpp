#include <iostream>
#include <utility>

int main() {
  int i = 8;
  int j = 9;
  int& x = i;
  i = std::move(j);  // 就是拷贝，因为 int 没有移动构造函数
  std::cout << x << std::endl;
  std::cout << i << std::endl;
  std::cout << j << std::endl;
  return 0;
}