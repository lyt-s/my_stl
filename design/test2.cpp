

// #include <cstddef>
// #include <iostream>
// #include <stack>
// #include <vector>
#include <bits/stdc++.h>
struct TreeNode {
  int m_val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int val = -1) : m_val(val), left(nullptr), right(nullptr) {}
};

std::vector<int> inorder(TreeNode *node) {
  std::vector<int> res;
  if (node == nullptr) {
    return res;
  }
  TreeNode *cur = node;
  std::stack<TreeNode *> st;
  while (cur || !st.empty()) {
    if (cur) {
      st.push(cur);
      cur = cur->left;
    } else {
      cur = st.top();
      st.pop();
      res.push_back(cur->m_val);
      cur = cur->right;
    }
  }
  return res;
}

class Logger {
 public:
  virtual void log(const char *msg) { printf("%s", msg); }
};

int main() {
  // std::vector<TreeNode *> res;
  // for (int i = 1; i < 6; i++) {
  //   res.push_back(new TreeNode(i));
  // }
  // for (int i = 0; i < 4; i++) {
  //   res[i]->left = nullptr;
  //   res[i]->right = res[i + 1];
  // }
  // res[4]->m_val = 5;
  // res[4]->left = nullptr;
  // res[4]->right = nullptr;
  // TreeNode *node = res[0];

  TreeNode *res = new TreeNode(1);
  TreeNode *node = res;
  for (int i = 2; i < 6; i++) {
    res->left = nullptr;
    res->right = new TreeNode(i);
    res = res->right;
  }

  std::vector<int> nums = inorder(node);
  for (auto i : nums) {
    std::cout << i << " ";
  }

  // Logger *p = NULL;
  // p->log("abc");
};