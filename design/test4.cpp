#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

// 快速幂求模，用于计算逆元
long long modPow(long long base, long long exp, long long mod) {
  long long result = 1;
  while (exp > 0) {
    if (exp % 2 == 1) {
      result = (result * base) % mod;
    }
    base = (base * base) % mod;
    exp /= 2;
  }
  return result;
}

// 计算逆元
long long modInverse(long long n, long long mod) {
  return modPow(n, mod - 2, mod);
}

// 计算组合数 C(n, k) % mod
long long modBinom(long long n, long long k, long long mod) {
  long long result = 1;
  for (long long i = 1; i <= k; ++i) {
    result = (result * (n - i + 1)) % mod;
    result = (result * modInverse(i, mod)) % mod;
  }
  return result;
}

long long countBalancedSubsequences(const string &s, long long mod) {
  vector<int> freq(26, 0);

  // 统计每个字符的频率
  for (char c : s) {
    freq[c - 'a']++;
  }

  long long ans = 0;
  // 对于每对字符(a, b)，计算组合
  for (int i = 0; i < 26; ++i) {
    for (int j = i + 1; j < 26; ++j) {
      if (freq[i] > 0 && freq[j] > 0) {
        long long pairs = min(freq[i], freq[j]);
        for (long long p = 1; p <= pairs; ++p) {
          ans = (ans + (modBinom(freq[i], p, mod) * modBinom(freq[j], p, mod)) %
                           mod) %
                mod;
        }
      }
    }
  }

  return ans;
}

int main() {
  int n;
  cin >> n;  // 输入字符串长度
  string s;
  cin >> s;  // 输入字符串内容

  // 输出平衡子序列的数量模 10^9 + 7 的结果
  cout << countBalancedSubsequences(s, MOD) << endl;

  return 0;
}