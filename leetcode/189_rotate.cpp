

#include <algorithm>
#include <iostream>
#include <vector>
void rotate(std::vector<int>& nums, int k) {
  int n = nums.size();

  k %= n;
  std::reverse(nums.begin(), nums.end());
  std::reverse(nums.begin(), nums.begin() + k);
  std::reverse(nums.begin() + k, nums.end());
}

int main() {
  int n, k;
  std::cin >> n >> k;

  std::vector<int> nums(n, 0);
  for (int i = 0; i < n; i++) {
    std::cin >> nums[i];
  }

  rotate(nums, k);

  for (auto i : nums) {
    std::cout << i << " ";
  }

  return 0;
  // 7 3
  // 1 2 3 4 5 6 7
}