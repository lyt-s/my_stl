#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int MAXN = 100005;
vector<int> tree[MAXN];  // 树的邻接表表示
char colors[MAXN];       // 节点颜色
int blackCount[MAXN];    // 记录每个子树中黑色节点的数量
int maxBlack[MAXN];  // 记录删除每个红色节点后，剩余连通块中黑色节点数量的最大值

void dfs(int node, int parent) {
  blackCount[node] = (colors[node] == 'B' ? 1 : 0);
  for (int child : tree[node]) {
    if (child != parent) {
      dfs(child, node);
      blackCount[node] += blackCount[child];
    }
  }
}

void dfsMaxBlack(int node, int parent, int totalBlack) {
  for (int child : tree[node]) {
    if (child != parent) {
      int newTotalBlack =
          totalBlack - (colors[child] == 'B' ? blackCount[child] : 0);
      maxBlack[node] =
          max(maxBlack[node],
              newTotalBlack +
                  (colors[node] == 'B'
                       ? blackCount[node] - (colors[node] == 'B' ? 1 : 0)
                       : 0));
      dfsMaxBlack(child, node, newTotalBlack);
    }
  }
}

int main() {
  int n;
  cin >> n;
  string colorStr;
  cin >> colorStr;
  for (int i = 0; i < n; ++i) {
    colors[i] = colorStr[i];
  }
  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    cin >> u >> v;
    --u;
    --v;  // 将节点编号转换为从0开始
    tree[u].push_back(v);
    tree[v].push_back(u);
  }

  dfs(0, -1);  // 从根节点开始DFS，计算每个子树中黑色节点的数量
  int totalBlack = 0;
  for (int i = 0; i < n; ++i) {
    if (colors[i] == 'B') {
      totalBlack++;
    }
  }

  int maxVal = 0;
  for (int i = 0; i < n; ++i) {
    if (colors[i] == 'R') {
      dfsMaxBlack(i, -1, totalBlack);
      maxVal = max(maxVal, maxBlack[i]);
    }
  }

  cout << maxVal << endl;
  return 0;
}