#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  // 读取输入字符串
  string S;
  cin >> S;
  int n = S.length();

  // 使用一个常量来标识模数 1e9 + 7
  const int MOD = 1000000007;

  // 创建一个动态数组dp
  vector<long long> dp(n + 1, 0);
  // 初始化动态数组的第一个值
  dp[0] = 1;

  // 遍历字符串进行动态规划
  for (int i = 1; i <= n; ++i) {
    dp[i] = dp[i - 1];
    if (S[i - 1] == '1' && i > 1 && S[i - 2] == '0') {
      dp[i] += dp[i - 2];
    }
    dp[i] %= MOD;  // 对MOD取模
  }

  // 输出结果，构造的新字符串个数
  cout << dp[n] << endl;
  return 0;
}