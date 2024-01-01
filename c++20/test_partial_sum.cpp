#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

int main() {
  std::vector<int> v(10, 2);  // v = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2}

  std::cout << "The first " << v.size() << " even numbers are: ";
  // write the result to the cout stream
  std::partial_sum(v.cbegin(), v.cend(),
                   std::ostream_iterator<int>(std::cout, " "));
  std::cout << '\n';

  // write the result back to the vector v
  std::partial_sum(v.cbegin(), v.cend(), v.begin(), std::multiplies<int>());

  std::cout << "The first " << v.size() << " powers of 2 are: ";
  for (int n : v) std::cout << n << ' ';
  std::cout << '\n';
}