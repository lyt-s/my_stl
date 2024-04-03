#include <iostream>
#include <vector>

void adjustHeap(std::vector<int>& arr, int i, int n) {
  int temp = arr[i];
  for (int k = 2 * i + 1; k < n; k = 2 * k + 1) {
    // 找到左右子节点中较大的一个
    if (k + 1 < n && arr[k] < arr[k + 1]) {
      k++;
    }

    // 如果子节点大于父节点，则交换它们
    if (arr[k] > temp) {
      arr[i] = arr[k];
      i = k;
    } else {
      break;
    }
  }

  arr[i] = temp;
}

void heapSort(std::vector<int>& arr) {
  int n = arr.size();

  // 构建大顶堆
  for (int i = n / 2 - 1; i >= 0; i--) {
    adjustHeap(arr, i, n);
  }

  // 排序
  for (int i = n - 1; i >= 0; i--) {
    std::swap(arr[0], arr[i]);

    // 调整堆
    adjustHeap(arr, 0, i);
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