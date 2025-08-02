#include <iostream>
#include <sstream>
#include <string>
#include <vector>
void setZeroes(std::vector<std::vector<int>>& matrix) {
  int m = matrix.size();
  int n = matrix[0].size();

  int flagx = false, flagy = false;
  for (int i = 0; i < m; i++) {
    if (matrix[i][0] == 0) {
      flagy = true;
      break;
    }
  }

  for (int j = 0; j < n; j++) {
    if (matrix[0][j] == 0) {
      flagx = true;
      break;
    }
  }

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (matrix[i][j] == 0) {
        matrix[i][0] = 0;
        matrix[0][j] = 0;
      }
    }
  }

  for (int i = 1; i < m; i++) {
    for (int j = 1; j < n; j++) {
      if (matrix[i][0] == 0 || matrix[0][j] == 0) {
        matrix[i][j] = 0;
      }
    }
  }

  if (flagx) {
    for (int j = 0; j < n; j++) {
      matrix[0][j] = 0;
    }
  }
  if (flagy) {
    for (int i = 0; i < m; i++) {
      matrix[i][0] = 0;
    }
  }
}

int main() {
  std::vector<std::vector<int>> matrix;

  std::string line;

  std::getline(std::cin, line);

  std::stringstream ss(line);

  int num;
  char ch;
  std::vector<int> nums;
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

  setZeroes(matrix);
  for (auto nums : matrix) {
    for (auto num : nums) {
      std::cout << num << " ";
    }
    std::cout << std::endl;
  }
}