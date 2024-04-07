

#include <iostream>
#include <vector>
int lowBound(const std::vector<int>& nums, int target) {
  std::vector<int> res;
  int left = 0, right = nums.size() - 1;
  while (left <= right) {
    int mid = left + ((right - left) / 2);
    {
      if (nums[mid] < target) {
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }
  }
  return left;
}

std::vector<int> searchRange(const std::vector<int>& nums, int target) {
  int start = lowBound(nums, target);
  if (start == nums.size() || nums[start] != target) {
    return {-1, -1};
  }

  int end = lowBound(nums, target + 1) - 1;
  return {start, end};
}

int main() {
  std::vector<int> nums{5, 7, 7, 8, 8, 10};
  int target = 4;

  std::vector<int> a = searchRange(nums, target);
  std::cout << a[0] << " " << a[1] << std::endl;
  return 0;
}