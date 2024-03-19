#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  std::vector<int> vec;
  auto print = [&](std::vector<int> &vec) {
    for (auto it = vec.begin(); it != vec.end(); ++it) {
      std::cout << *it << " ";
    }
    std::cout << std::endl;
  };
  vec.emplace_back(1);
  vec.emplace_back(2);
  vec.emplace_back(3);
  vec.emplace_back(4);
  vec.emplace_back(5);
  vec.emplace_back(6);
  vec.emplace_back(7);
  vec.emplace_back(8);
  std::vector<int>::iterator it = vec.begin();
  while (it < vec.end()) {
    std::cout << *it << " ";
    it++;
  }
  std::cout << std::endl;
  auto pos = std::find(vec.begin(), vec.end(), 3);
  if (pos != vec.end()) {
    auto i = vec.insert(pos, 30);
  }
  print(vec);
  // 扩容时，导致迭代器变为野指针。会出现问题，删除错误。
  vec.erase(pos);

  print(vec);

  return 0;
}