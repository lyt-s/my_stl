#include <iostream>
#include <ostream>
#include <vector>

int partition(std::vector<int>& vec, int left, int right) {
  int privot = vec[left];
  int i = left;
  int j = right;
  while (i < j) {
    while (i < j && vec[j] >= privot) {
      j--;
    }
    vec[i] = vec[j];
    while (i < j && vec[i] <= privot) {
      i++;
    }
    vec[j] = vec[i];
  }
  vec[i] = privot;
  return i;
}

void quickSort(std::vector<int>& vec, int left, int right) {
  if (left < right) {
    int index = partition(vec, left, right);
    quickSort(vec, left, index - 1);
    quickSort(vec, index + 1, right);
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