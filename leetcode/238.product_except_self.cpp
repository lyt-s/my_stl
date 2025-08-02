#include <iostream>
#include <vector>
std::vector<int> productExceptSelf(std::vector<int>& nums) {
  std::vector<int> result(nums.size(), 1);

  for (int i = 1; i < nums.size(); ++i) {
    result[i] = result[i - 1] * nums[i - 1];
  }
  int temp = 1;
  for (int i = nums.size() - 2; i >= 0; --i) {
    temp *= nums[i + 1];
    result[i] *= temp;
  }
  return result;
}

int main() {
  std::vector<int> nums{1, 2, 3, 4};
  std::vector<int> result = productExceptSelf(nums);

  for (auto i : result) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
}