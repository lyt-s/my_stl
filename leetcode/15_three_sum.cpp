#include <algorithm>
#include <iostream>
#include <ostream>
#include <vector>

std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
  std::vector<std::vector<int>> result;
  std::sort(nums.begin(), nums.end());

  for (int i = 0; i < nums.size(); i++) {
    if (i > 0 && nums[i - 1] == nums[i]) {
      continue;
    }
    if (nums[i] > 0) {
      break;
    }

    int left = i + 1;
    int right = nums.size() - 1;
    while (left < right) {
      int sum = nums[i] + nums[left] + nums[right];
      if (sum > 0) {
        right--;
      } else if (sum < 0) {
        left++;
      } else {
        result.push_back({nums[i], nums[left], nums[right]});
        while (left < right && nums[left] == nums[left + 1]) {
          left++;
        }
        while (left < right && nums[right] == nums[right - 1]) {
          right--;
        }
        left++;
        right--;
      }
    }
  }
  return result;
}

int main() {
  int n;
  std::vector<int> nums(n, 0);
  for (int i = 0; i < n; i++) {
    std::cin >> nums[i];
  }

  std::vector<std::vector<int>> result = threeSum(nums);

  for (auto nums : result) {
    std::cout << '[';
    for (auto i : nums) {
      std::cout << i << " ";
    }
    std::cout << ']' << std::endl;
  }
  // 6
  // -1 0 1 2 -1 -4
}