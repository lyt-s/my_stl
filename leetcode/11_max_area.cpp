#include <algorithm>
#include <iostream>
#include <vector>
int maxArea(std::vector<int>& height) {
  int left = 0;
  int right = height.size() - 1;
  int result = 0;
  while (left < right) {
    int h = std::min(height[left], height[right]);
    int w = right - left;
    int area = h * w;
    result = std::max(area, result);
    if (height[left] <= height[right]) {
      left++;
    } else {
      right--;
    }
  }
  return result;
}

int main() {
  int n;
  std::cin >> n;
  std::vector<int> height(n, 0);
  for (int i = 0; i < n; i++) {
    std::cin >> height[i];
  }

  std::cout << maxArea(height) << std::endl;
  return 0;
  // 9
  // 1 8 6 2 5 4 8 3 7
}