#include <cstdio>
#include <cstdlib>
void print_arr(int arr[], int n) {
  for (int i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }
  putchar('\n');
}

void merge(int arr[], int tempArr[], int left, int mid, int right) {
  // 标记左半区第一个未排序的数组
  int l_pos = left;
  // 标记右半区第一个未排序的数组
  int r_pos = mid + 1;
  // 临时数组下标
  int pos = left;
  // 合并
  while (l_pos <= mid && r_pos <= right) {
    if (arr[l_pos] < arr[r_pos]) {  // 左半区第一个剩余元素最小 稳定的
      tempArr[pos++] = arr[l_pos++];
    } else {
      tempArr[pos++] = arr[r_pos++];
    }
  }
  // 合并左半区域剩余元素
  while (l_pos <= mid) {
    tempArr[pos++] = arr[l_pos++];
  }
  // 合并右半区剩余元素
  while (r_pos <= right) {
    tempArr[pos++] = arr[r_pos++];
  }
  // 把临时数组中合并后的元素复制回原来的数组
  while (left <= right) {
    arr[left] = tempArr[left];
    left++;
  }
}

// 归并排序

void msort(int arr[], int tempArr[], int left, int right) {
  // 如果只有一个元素，就不需要继续进行划分
  if (left < right) {
    // 找中间点
    int mid = (left + right) / 2;
    // 递归划分左半区域
    msort(arr, tempArr, left, mid);
    // 递归划分右半区域
    msort(arr, tempArr, mid + 1, right);
    // 合并已排序的部分
    merge(arr, tempArr, left, mid, right);
  }
}

void merge_sort(int arr[], int n) {
  // 分配一个辅助的数组
  int *tempArr = (int *)malloc(n * sizeof(int));

  if (tempArr) {  // 辅助数组分配成功
    msort(arr, tempArr, 0, n - 1);
    free(tempArr);
  } else {
    printf("error failed to allocate memory");
  }
}

int main() {
  int arr[] = {9, 5, 2, 7, 12, 4, 3, 1, 11};
  int n = 9;

  print_arr(arr, n);
  merge_sort(arr, n);
  print_arr(arr, n);
}
