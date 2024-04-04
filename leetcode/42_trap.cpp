
#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

int trap(std::vector<int>& nums) {
  if (nums.size() <= 2) {
    return 0;
  }
  int result = 0;
  std::stack<int> st;
  st.push(0);

  for (int i = 1; i < nums.size(); ++i) {
    if (nums[i] < nums[st.top()]) {
      st.push(i);
    } else if (nums[i] == nums[st.top()]) {
      st.pop();
      st.push(i);
    } else {
      while (!st.empty() && nums[i] > nums[st.top()]) {
        int mid = st.top();
        st.pop();
        if (!st.empty()) {
          int h = std::min(nums[i], nums[st.top()]) - nums[mid];
          int w = i - st.top() - 1;
          result += h * w;
        }
      }
      st.push(i);
    }
  }
  return result;
}

int main() {
  int n;
  std::cin >> n;
  std::vector<int> nums(n, 0);
  for (int i = 0; i < n; i++) {
    std::cin >> nums[i];
  }

  std::cout << trap(nums) << std::endl;

  //   6
  // 4 2 0 3 2 5
}