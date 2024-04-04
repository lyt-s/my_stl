

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
std::vector<int> spiralOrder(std::vector<std::vector<int>>& matrix) {
  std::vector<int> result;
  int left = 0;
  int right = matrix[0].size() - 1;
  int up = 0;
  int down = matrix.size() - 1;

  while (true) {
    for (int j = left; j <= right; j++) {
      result.push_back(matrix[up][j]);
    }
    if (++up > down) break;

    for (int i = up; i <= down; i++) {
      // std::cout << matrix[i][right];
      result.push_back(matrix[i][right]);
    }
    if (--right < left) break;
    for (int j = right; j >= left; j--) {
      result.push_back(matrix[down][j]);
    }
    if (--down < up) break;

    for (int i = down; i >= up; i--) {
      result.push_back(matrix[i][left]);
    }
    if (++left > right) break;
  }
  return result;
}

int main() {
  std::string line("[[1,2,3],[4,5,6],[7,8,9]]");
  // std::getline(std::cin, line);
  std::stringstream ss(line);

  int num;
  char ch;
  std::vector<int> nums;
  std::vector<std::vector<int>> matrix;

  while (ss >> ch) {
    if (ch == '[' || ch == ',') {
      continue;
    }
    if (ch == ']') {
      if (nums.size()) {
        matrix.push_back(nums);
        nums.clear();
      }
    } else {
      ss.unget();
      if (ss >> num) {
        nums.push_back(num);
      }
    }
  }

  nums = spiralOrder(matrix);

  for (int i = 0; i < nums.size(); i++) {
    std::cout << nums[i] << " ";
  }
  return 0;
}