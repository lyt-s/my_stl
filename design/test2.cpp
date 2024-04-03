#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  vector<int> cnt(n);
  unordered_map<int, int> counts;

  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  // Create a prefix sum array
  for (int i = 0; i < n; ++i) {
    counts[a[i]]++;
    cnt[i] = counts[a[i]];
  }

  // Create a suffix max count array
  counts.clear();
  vector<int> max_cnt(n);
  for (int i = n - 1; i >= 0; --i) {
    counts[a[i]]++;
    if (i == n - 1) {
      max_cnt[i] = counts[a[i]];
    } else {
      max_cnt[i] = max(max_cnt[i + 1], counts[a[i]]);
    }
  }

  int result = 0;

  // Calculate the number of valid pairs
  for (int i = 0; i < n - 1; ++i) {
    for (int j = i + 1; j < n; ++j) {
      if (cnt[i] > max_cnt[j]) {
        result++;
      }
    }
  }

  cout << result << endl;
  return 0;
}