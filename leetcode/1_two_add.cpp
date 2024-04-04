
#include <iostream>
#include <unordered_map>
#include <vector>

std::vector<int> twoSum(std::vector<int>& nums, int target) {
  std::vector<int> result;
  std::unordered_map<int, int> hash;

  for (int i = 0; i < nums.size(); ++i) {
    if (hash.count(target - nums[i])) {
      result.push_back(hash[target - nums[i]]);
      result.push_back(i);
      break;
    }
    hash[nums[i]] = i;
  }
  return result;
}

int main() {
  int n, target;
  std::cin >> n;
  std::vector<int> nums(n, 0);
  for (int i = 0; i < n; i++) {
    std::cin >> nums[i];
  }

  std::cin >> target;

  std::vector<int> result = twoSum(nums, target);
  for (auto i : result) {
    std::cout << i << " ";
  }

  return 0;
}