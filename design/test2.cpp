#include <iostream>
#include <vector>

#include "stdio.h"
class A {
 public:
  void f1() { printf("A::f1\n"); }

  virtual void f2() { printf("A::f2\n"); }
};
class B {
 public:
  virtual void f1() { printf("B::f1\n"); }

  virtual void f2() { printf("B::f2\n"); }
};

int partition(std::vector<int> &arr, int left, int right) {
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

void sort(std::vector<int> &nums, int left, int right) {
  if (left < right) {
    int mid = partition(nums, left, right);
    sort(nums, left, mid - 1);
    sort(nums, mid + 1, right);
  }
}

int main() {
  std::vector<int> nums{1, 3, 5, 4, 2, 9, 7, 8, 6};
  sort(nums, 0, nums.size() - 1);
  for (auto i : nums) {
    std::cout << i << " ";
  }
  int x = 10;
  int y = 9;
  int &pt = x;
  B b;
  A *p = (A *)&b;
  p->f1();
  p->f2();
  return 0;
}