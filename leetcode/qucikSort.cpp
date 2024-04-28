#include <iostream>
#include <vector>

int partition(std::vector<int>& arr, int left, int right) {
  int privot = arr[left];
  while (left < right) {
    while (left < right && arr[right] >= privot) {
      right--;
    }
    arr[left] = arr[right];
    while (left < right && arr[left] <= privot) {
      left++;
    }
    arr[right] = arr[left];
  }
  arr[left] = privot;
  return left;
}

void quickSort(std::vector<int>& arr, int left, int right) {
  if (left < right) {
    int mid = partition(arr, left, right);
    quickSort(arr, left, mid - 1);
    quickSort(arr, mid + 1, right);
  }
}

int main() {
  std::vector<int> arr = {3, 6, 7, 8, 9, 1, 4, 5};
  quickSort(arr, 0, arr.size() - 1);
  for (auto num : arr) {
    std::cout << num << " ";
  }
  return 0;
}