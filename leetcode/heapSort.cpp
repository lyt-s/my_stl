

#include <iostream>
#include <vector>

void adjustHeap(std::vector<int>& arr, int n, int i) {
  int largest = i;
  int l_son = i * 2 + 1;
  int r_son = i * 2 + 2;

  if (l_son < n && arr[largest] < arr[l_son]) {
    largest = l_son;
  }

  if (r_son < n && arr[largest] < arr[r_son]) {
    largest = r_son;
  }

  if (i != largest) {
    std::swap(arr[largest], arr[i]);
    adjustHeap(arr, n, largest);
  }
}

void heapSort(std::vector<int>& arr) {
  int n = arr.size();

  // 构建堆
  for (int i = n / 2 - 1; i >= 0; i--) {
    adjustHeap(arr, n, i);
  }

  // paixu

  for (int i = n - 1; i >= 0; i--) {
    std::swap(arr[0], arr[i]);
    adjustHeap(arr, i, 0);
  }
}

int main() {
  std::vector<int> arr{4, 5, 3, 2, 6, 9, 8, 7, 0};

  heapSort(arr);
  for (auto i : arr) {
    std::cout << i << " ";
  }
  std::cout << '\n';
}