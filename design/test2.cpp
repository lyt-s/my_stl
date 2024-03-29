#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  int n, x;
  cin >> n >> x;

  vector<int> fans(n);
  for (int i = 0; i < n; ++i) {
    cin >> fans[i];
  }
  sort(fans.rbegin(), fans.rend());

  int sum = 0, accounts = 0;
  bool usedExtraPost = false;

  for (int i = 0; i < n; ++i) {
    if (!usedExtraPost && sum + fans[i] >= x) {
      sum += fans[i];
      accounts++;
      break;
    }
    sum += fans[i] / 2;
    accounts++;
    if (sum >= x) {
      break;
    }
  }
  if (sum < x) {
    cout << -1 << endl;
  } else {
    cout << accounts << endl;
  }

  return 0;
}