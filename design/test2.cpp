#include <bits/stdc++.h>
using namespace std;

int getDistance(pair<int, int> a, pair<int, int> b) {
  return abs(a.first - b.first) + abs(a.second - b.second);
}

int getMinCost(pair<int, int> init, pair<int, int> target,
               vector<pair<int, int>> nodes) {
  int min = INT_MAX, min_i = 0, res = 0;

  for (int i = 0; i < nodes.size(); ++i) {
    int d1 = getDistance(init, nodes[i]);
    int d2 = getDistance(target, nodes[i]);
    int diff = d2 + d1 - 2 * d2;
    if (diff < min) {
      min = diff;
      min_i = i;
    }
  }

  for (int i = 0; i < nodes.size(); ++i) {
    int d1 = getDistance(init, nodes[i]);
    int d2 = getDistance(target, nodes[i]);
    if (i == min_i) {
      res += d1 + d2;
    } else {
      res += 2 * d2;
    }
  }

  return res;
}

int main() {
  pair<int, int> init, target;
  vector<pair<int, int>> nodes;
  int n;
  cin >> init.first >> init.second >> target.first >> target.second;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    nodes.emplace_back(0, 0);
    cin >> nodes.back().first >> nodes.back().second;
  }
  cout << getMinCost(init, target, nodes) << endl;
  return 0;
}
// 64 位输出请用 printf("%lld")