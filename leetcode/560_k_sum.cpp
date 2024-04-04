#include <iostream>
#include <ostream>
#include <unordered_map>
#include <vector>

int KSum(std::vector<int>& nums, int target) {
  int prefix = 0;
  std::unordered_map<int, int> hash;
  hash[0] = 1;
  int result = 0;
  for (int i = 0; i < nums.size(); i++) {
    prefix += nums[i];
    if (hash.count(prefix - target) == 1) {
      result += hash[prefix - target];
    }
    hash[prefix]++;
  }
  return result;
}

int main() {
  int n, target;
  std::cin >> n >> target;

  std::vector<int> nums(n, 0);
  for (int i = 0; i < n; i++) {
    std::cin >> nums[i];
  }

  std::cout << KSum(nums, target) << std::endl;
  return 0;
  // 3  2
  // 1 1 1
}
