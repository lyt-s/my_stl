#include <iostream>
#include <vector>

using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int& x : a) cin >> x;

  int answer = 0;

  // 对于每对可能的i和j，计算满足条件的对数
  for (int i = 0; i < n; ++i) {
    int countLeft = 0;  // 记录a[i]在数组左半部分的出现次数

    // 计算a[i]在区间[1, i]出现的次数
    for (int l = 0; l <= i; ++l) {
      if (a[l] == a[i]) ++countLeft;
    }

    // 对于每个可能的j > i，计算a[j]在区间[j, n]出现的次数
    for (int j = i + 1; j < n; ++j) {
      int countRight = 0;  // 记录a[j]在数组右半部分的出现次数

      // 计算a[j]在区间[j, n]出现的次数
      for (int r = j; r < n; ++r) {
        if (a[r] == a[j]) ++countRight;
      }

      // 如果 a[i] 在左侧的出现次数大于 a[j] 在右侧的出现次数，增加答案.
      if (countLeft > countRight) ++answer;
    }
  }

  cout << answer << endl;
  return 0;
}