#include <iostream>

int partition(int arr[], int low, int high) {
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

void quickSort(int arr[], int low, int high) {
  if (low < high) {
    int pivotIndex = partition(arr, low, high);
    quickSort(arr, low, pivotIndex - 1);
    quickSort(arr, pivotIndex + 1, high);
  }
}

int main() {
  int arr[] = {3, 6, 7, 8, 9, 1, 4, 5};
  int len = sizeof(arr) / sizeof(arr[0]);
  quickSort(arr, 0, len - 1);
  for (auto num : arr) {
    std::cout << num << " ";
  }
  return 0;
}