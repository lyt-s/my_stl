#include <iostream>
#include <string>
using namespace std;

// 检查是否可通过最多k次操作将所有子串长度缩短至mid及以下
bool isValid(const string& s, int k, int mid) {
  int count = 0, ops = 0;
  for (char c : s) {
    if (c == '1') {
      if (++count > mid) {
        count = 1;
        ops++;
      }
    } else {
      if (count > mid) {
        ops++;
      }
      count = 0;
    }
  }
  // 增加对尾部处理
  if (count > mid) {
    ops++;
  }
  return ops <= k;
}

int minMaxLen(string s, int k) {
  int left = 1, right = s.size();  // 重新设定搜索范围
  int mid, ans = right;

  while (left <= right) {
    mid = left + (right - left) / 2;
    if (isValid(s, k, mid)) {
      ans = mid;
      right = mid - 1;
    } else {
      left = mid + 1;
    }
  }

  return ans;
}

int main() {
  string s = "10111110110";
  int k = 1;
  cout << minMaxLen(s, k) << endl;
  return 0;
}