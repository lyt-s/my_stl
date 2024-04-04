#include <iostream>
#include <vector>

using namespace std;
void setZeroes(vector<vector<int>>& matrix) {
  int rows = matrix.size();
  int cols = matrix[0].size();
  int flagx = false, flagy = false;
  for (int i = 0; i < rows; ++i) {
    if (matrix[i][0] == 0) {
      flagy = true;
      // break;
    }
  }
  for (int j = 0; j < cols; j++) {
    if (matrix[0][j] == 0) {
      flagx = true;
      // break;
    }
  }

  for (int i = 1; i < rows; ++i) {
    for (int j = 1; j < cols; ++j) {
      if (!matrix[i][j]) {
        matrix[i][0] = 0;
        matrix[0][j] = 0;
      }
    }
  }

  for (int i = 1; i < rows; ++i) {
    for (int j = 1; j < cols; ++j) {
      if (matrix[i][0] == 0 || matrix[0][j] == 0) {
        matrix[i][j] = 0;
      }
    }
  }

  if (flagx) {
    for (int i = 0; i < rows; ++i) {
      matrix[0][i] = 0;
    }
  }
  if (flagy) {
    for (int j = 0; j < cols; ++j) {
      matrix[j][0] = 0;
      cout << matrix[0][j];
    }
  }
}

int main() {
  vector<vector<int>> matrix(1, {1, 0, 3});
  setZeroes(matrix);

  for (auto nums : matrix) {
    for (auto i : nums) {
      cout << i << " ";
    }
    cout << endl;
  }
  return 0;
}