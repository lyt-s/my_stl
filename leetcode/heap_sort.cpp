#include <iostream>
#include <utility>
#include <vector>

// 维护堆的性质
void heapify(std::vector<int>& arr, int i, int n) {
  int largest = i;
  int lson = i * 2 + 1;
  int rson = i * 2 + 2;
  if (lson < n && arr[largest] < arr[lson]) {
    largest = lson;
  }
  if (rson < n && arr[largest] < arr[rson]) {
    largest = rson;
  }
  if (largest != i) {
    std::swap(arr[largest], arr[i]);
    heapify(arr, largest, n);
  }
}

// 维护堆的性质
void heapify_low(std::vector<int>& arr, int i, int n) {
  int largest = i;
  int lson = i * 2 + 1;
  int rson = i * 2 + 2;
  if (lson < n && arr[largest] > arr[lson]) {
    largest = lson;
  }
  if (rson < n && arr[largest] > arr[rson]) {
    largest = rson;
  }
  if (largest != i) {
    std::swap(arr[largest], arr[i]);
    heapify(arr, largest, n);
  }
}

// 下标位i的节点的父节点，下标位 (i-1)/2
// i * 2 + 1
// i * 2 + 2
void heapSort(std::vector<int>& arr) {
  int n = arr.size();

  // 构建大顶堆, i的父节点, 下标为 i-1/2
  // (n -1 -1)/2
  for (int i = n / 2 - 1; i >= 0; i--) {
    heapify_low(arr, i, n);
  }

  // 排序
  for (int i = n - 1; i >= 0; i--) {
    std::swap(arr[0], arr[i]);
    // 调整堆
    // 现在维护的堆的个数为 n-1
    heapify_low(arr, 0, i);
  }
}

int main() {
  std::vector<int> arr = {3, 6, 8, 2, 4, 1, 9, 5, 7};
  heapSort(arr);
  for (int num : arr) {
    std::cout << num << " ";
  }
  return 0;
}