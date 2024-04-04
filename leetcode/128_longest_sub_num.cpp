#include <algorithm>
#include <iostream>
#include <iterator>
#include <unordered_set>
#include <vector>

int longest(std::vector<int>& nums) {
  std::unordered_set<int> hash;
  int result = 0;

  for (auto num : nums) {
    hash.insert(num);
  }

  for (auto num : nums) {
    {
      if (hash.count(num - 1) == 0) {
        int temp = 0;
        while (hash.count(num++)) {
          temp++;
        }
        result = std::max(temp, result);
      }
    }
  }
  return result;
}

int main() {
  int n;
  std::cin >> n;
  std::vector<int> nums(n, 0);
  for (int i = 0; i < n; i++) {
    std::cin >> nums[i];
  }

  std::cout << longest(nums) << std::endl;
  return 0;
}