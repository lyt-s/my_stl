#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  int n, x;
  cin >> n >> x;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  vector<int> accounts(2 * n);
  for (int fan : a) {
    accounts.emplace_back(fan);      // 完整粉丝数和其次数
    accounts.emplace_back(fan / 2);  // 一半粉丝数和其次数
  }
  sort(a.begin(), a.end());
  // 动态规划数组初始化，其中dp[i]存储获取到i个粉丝所需的最少账号数量
  vector<int> dp(x + 1, INT_MAX);
  dp[0] = 0;  // 0个粉丝需要0个账号
  int result = INT_MAX;

  // 不选择多次发推荐文章的账号，计算每一个粉丝数其所需的最少的账号数量
  for (int i = 0; i < a.size(); i++) {
    for (int j = x; j >= a[i]; j--) {
      if (dp[j - a[i]] != INT_MAX) {
        dp[j] = min(dp[j], dp[j - a[i]] + 1);
      }
    }
    result = min(result, dp[x]);
  }

  // 输出结果，如果无法达到x粉丝数则输出-1
  if (result == INT_MAX) {
    cout << -1 << endl;
  } else {
    cout << result << endl;
  }

  return 0;
}