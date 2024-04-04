

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
bool searchMatrix(std::vector<std::vector<int>>& matrix, int target) {
  int i = 0;
  int j = matrix[0].size() - 1;

  while (i < matrix.size() && j >= 0) {
    if (matrix[i][j] > target) {
      j--;
    } else if (matrix[i][j] < target) {
      i++;
    } else {
      return true;
    }
  }
  return false;
}

int main() {
  std::string line;
  int target;
  std::getline(std::cin, line);
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
      ss >> num;
      nums.push_back(num);
    }
  }
  std::cin >> target;
  std::cout << searchMatrix(matrix, target);
}