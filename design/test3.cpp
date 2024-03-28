#include <bits/stdc++.h>
using namespace std;

// 定义箱子的结构体
struct Box {
  int h, w, l;
};

// 比较函数，用于排序
bool compareBox(Box b1, Box b2) { return (b1.l * b1.w) > (b2.l * b2.w); }

int maxStackHeight(Box arr[], int n) {
  sort(arr, arr + n, compareBox);

  int dp[n];
  for (int i = 0; i < n; i++) dp[i] = arr[i].h;

  int maxValue = dp[0];

  for (int i = 1; i < n; i++) {
    for (int j = 0; j < i; j++) {
      if (arr[i].w < arr[j].w && arr[i].l < arr[j].l &&
          dp[i] < dp[j] + arr[i].h) {
        dp[i] = dp[j] + arr[i].h;
        maxValue = max(maxValue, dp[i]);
      }
    }
  }
  return maxValue;
}

int main() {
  Box arr[] = {{1, 1, 1}, {2, 2, 2}, {1, 2, 4}};
  int n = sizeof(arr) / sizeof(arr[0]);

  cout << "The maximum possible height of stack is " << maxStackHeight(arr, n);
  return 0;
}