#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main() {
  std::cout << "make_reverse_iterator -----------" << std::endl;
  std::vector<int> v{1, 3, 10, 8, 22};

  std::sort(v.begin(), v.end());
  std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, ", "));
  std::cout << '\n';

  std::copy(std::make_reverse_iterator(v.end()),
            std::make_reverse_iterator(v.begin()),
            std::ostream_iterator<int>(std::cout, ", "));
  std::cout << '\n';

  std::cout << "base -----------" << std::endl;

  std::vector<int> vec{1, 3, 10, 8, 22};
  auto rit = vec.begin();  // 获取反向迭代器

  // 从 vec.begin() 到 vec.end() 的范围逆向复制到 std::cout 中
  std::copy(vec.rbegin(), vec.rend(),
            std::ostream_iterator<int>(std::cout, ", "));
  std::cout << '\n';
}
