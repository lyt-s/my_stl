#include <cstdlib>
#include <iostream>
#include <ostream>
#include <vector>

int partition(std::vector<int>& nums, int left, int right) {
  int privot = nums[left];
  while (left < right) {
    while (left < right && nums[right] >= privot) {
      right--;
    }
    nums[left] = nums[right];
    while (left < right && nums[left] <= privot) {
      left++;
    }
    nums[right] = nums[left];
  }
  nums[left] = privot;
  return left;
}

void quickSort(std::vector<int>& nums, int left, int right) {
  if (left < right) {
    int mid = partition(nums, left, right);
    quickSort(nums, mid + 1, right);
    quickSort(nums, 0, mid - 1);
  }
}

int main() {
  std::vector<int> vec{1, 4, 3, 2, 7, 5, 6, 8, 0, 9};
  quickSort(vec, 0, vec.size() - 1);

  for (auto i : vec) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
}