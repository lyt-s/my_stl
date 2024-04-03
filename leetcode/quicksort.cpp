#include <iostream>
#include <ostream>
#include <vector>

int partition(std::vector<int>& arr, int low, int high) {
  int pivot = arr[low];
  int i = low;
  int j = high;
  while (i < j) {
    while (i < j && arr[j] >= pivot) {
      j--;
    }
    arr[i] = arr[j];
    while (i < j && arr[i] <= pivot) {
      i++;
    }
    arr[j] = arr[i];
  }
  arr[i] = pivot;
  return i;
}

void quickSort(std::vector<int>& arr, int low, int high) {
  if (low < high) {
    int pivotIndex = partition(arr, low, high);
    quickSort(arr, low, pivotIndex - 1);
    quickSort(arr, pivotIndex + 1, high);
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