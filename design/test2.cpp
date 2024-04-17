#include <bits/stdc++.h>
using namespace std;

unordered_map<string, pair<int, string>> trees;  // 边
unordered_map<string, int> total_problems;       // 每颗树的问题数量

string find_root(string node) {
  if (trees[node].second == node) {
    return node;
  } else {
    return trees[node].second = find_root(trees[node].second);
  }
}

void process_tree() {
  for (auto &edge : trees) {
    string root = edge.second.second;
    if (total_problems.find(root) != total_problems.end()) {
      total_problems[root] += edge.second.first;
      continue;
    }
    edge.second.second = find_root(edge.second.second);
    total_problems[edge.second.second] += edge.second.first;
  }
}

int main() {
  int M, N;
  cin >> M >> N;
  for (int i = 0; i < N; ++i) {
    string Ai, Bi;
    int Ci, Di;
    cin >> Ai >> Bi >> Ci >> Di;
    int problem = 0;
    if (Ci == 0) {
      problem += 5 * Di;
    } else {
      problem += 2 * Di;
    }
    trees[Ai].first += problem;
    if (Bi == "*") {
      trees[Ai].second = Ai;
      total_problems.insert({Ai, 0});
    } else {
      trees[Ai].second = Bi;
    }
  }
  process_tree();
  int res = 0;
  for (auto &problem : total_problems) {
    if (problem.second > M) {
      res++;
    }
  }
  cout << res << endl;
  return 0;
}