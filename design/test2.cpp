// #include <algorithm>
// #include <climits>
// #include <iostream>
// #include <queue>
// #include <vector>

// using namespace std;

// struct State {
//   int x, y, gold, usedSkill;
//   State(int _x, int _y, int _gold, int _usedSkill)
//       : x(_x), y(_y), gold(_gold), usedSkill(_usedSkill) {}
// };

// int maxGold(vector<vector<int>>& grid) {
//   int m = grid.size();
//   int n = grid[0].size();
//   vector<vector<vector<int>>> dp(
//       m, vector<vector<int>>(n, vector<int>(2, INT_MIN)));

//   queue<State> q;
//   if (grid[0][0] != -1) {
//     q.emplace(0, 0, grid[0][0], 0);
//     dp[0][0][0] = grid[0][0];
//   }

//   int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
//   int maxGoldCollected = 0;

//   while (!q.empty()) {
//     auto [x, y, gold, usedSkill] = q.front();
//     q.pop();

//     maxGoldCollected = max(maxGoldCollected, gold);

//     for (auto& dir : directions) {
//       int nx = x + dir[0], ny = y + dir[1];
//       if (nx >= 0 && ny >= 0 && nx < m && ny < n) {
//         if (grid[nx][ny] != -1 && gold + grid[nx][ny] >
//         dp[nx][ny][usedSkill]) {
//           dp[nx][ny][usedSkill] = gold + grid[nx][ny];
//           q.emplace(nx, ny, dp[nx][ny][usedSkill], usedSkill);
//         } else if (grid[nx][ny] == -1 && usedSkill == 0 &&
//                    gold > dp[nx][ny][1]) {
//           dp[nx][ny][1] = gold;
//           q.emplace(nx, ny, gold, 1);
//         }
//       }
//     }
//   }

//   return maxGoldCollected;
// }

// int main() {
//   vector<vector<int>> grid1 = {{1, -1}, {-1, 1}};
//   cout << maxGold(grid1) << endl;  // Output: 2

//   vector<vector<int>> grid2 = {{-1}};
//   cout << maxGold(grid2) << endl;  // Output: 0

//   return 0;
// }
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

// 使用BFS算法找到从start到end的最短路径
int bfs(const unordered_map<int, vector<int>>& graph, int start, int end) {
  if (start == end) return 0;
  queue<pair<int, int>> q;  // 队列中存储节点编号和从start到当前节点的跳数
  unordered_map<int, bool> visited;  // 记录节点是否被访问过
  q.push({start, 0});
  visited[start] = true;

  while (!q.empty()) {
    auto [node, distance] = q.front();
    q.pop();
    for (int neighbor : graph.at(node)) {
      if (neighbor == end) return distance + 1;
      if (!visited[neighbor]) {
        q.push({neighbor, distance + 1});
        visited[neighbor] = true;
      }
    }
  }
  return -1;  // 如果没有找到路径，则返回-1
}

int main() {
  int n, m;
  cin >> n >> m;
  unordered_map<string, int> ipToId;
  unordered_map<int, vector<int>> graph;
  string ip;
  int id;

  // 读取IP地址和编号
  for (int i = 0; i < n; ++i) {
    cin >> ip >> id;
    ipToId[ip] = id;
  }

  // 构建图
  int a, b;
  for (int i = 0; i < m; ++i) {
    cin >> a >> b;
    graph[a].push_back(b);
    graph[b].push_back(a);  // 无向图
  }

  int q;
  cin >> q;
  string startIp, endIp;

  // 对于每对需要判断连通性的IP地址
  for (int i = 0; i < q; ++i) {
    cin >> startIp >> endIp;
    if (ipToId.find(startIp) == ipToId.end() ||
        ipToId.find(endIp) == ipToId.end()) {
      cout << -1 << endl;  // 如果IP地址不存在，则输出-1
      continue;
    }
    int startId = ipToId[startIp];
    int endId = ipToId[endIp];
    cout << bfs(graph, startId, endId) << endl;
  }

  return 0;
}