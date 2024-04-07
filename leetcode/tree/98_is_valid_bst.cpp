

#include <iostream>
#include <queue>
#include <vector>
using namespace std;
struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int value = 0) : val(value), left(nullptr), right(nullptr) {}
};

TreeNode* createBinaryTree(const std::vector<int>& nums) {
  std::vector<TreeNode*> vecTree(nums.size(), nullptr);
  TreeNode* root = nullptr;
  for (int i = 0; i < nums.size(); i++) {
    TreeNode* node = nullptr;
    if (nums[i] != -1) {
      node = new TreeNode(nums[i]);
    }
    vecTree[i] = node;
    if (i == 0) {
      root = node;
    }
  }

  for (int i = 0; i * 2 + 1 < nums.size(); i++) {
    if (vecTree[i] != NULL) {
      vecTree[i]->left = vecTree[i * 2 + 1];
      if (i * 2 + 2 < vecTree.size()) {
        vecTree[i]->right = vecTree[i * 2 + 2];
      }
    }
  }
  return root;
}

// 层序打印打印二叉树
void print_binary_tree(TreeNode* root) {
  queue<TreeNode*> que;
  if (root != NULL) que.push(root);
  vector<vector<int>> result;
  while (!que.empty()) {
    int size = que.size();
    vector<int> vec;
    for (int i = 0; i < size; i++) {
      TreeNode* node = que.front();
      que.pop();
      if (node != NULL) {
        vec.push_back(node->val);
        que.push(node->left);
        que.push(node->right);
      }
      // 这里的处理逻辑是为了把null节点打印出来，用-1 表示null
      else
        vec.push_back(-1);
    }
    result.push_back(vec);
  }
  for (int i = 0; i < result.size(); i++) {
    for (int j = 0; j < result[i].size(); j++) {
      cout << result[i][j] << " ";
    }
    cout << endl;
  }
}

int main() {
  vector<int> vec = {4, 1, 6, 0, 2, 5, 7, -1, -1, -1, 3, -1, -1, -1, 8};
  TreeNode* root = createBinaryTree(vec);
  print_binary_tree(root);
}