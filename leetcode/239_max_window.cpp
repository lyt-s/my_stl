
#include <deque>
#include <iostream>
#include <vector>
std::vector<int> maxWindowSize(std::vector<int>& nums, int k) {
  std::deque<int> que;
  std::vector<int> result;

  for (int i = 0; i < k; ++i) {
    while (!que.empty() && que.back() < nums[i]) {
      que.pop_back();
    }
    que.push_back(nums[i]);
  }
  result.push_back(que.front());

  for (int i = k; i < nums.size(); ++i) {
    if (nums[i - k] == que.front()) {
      que.pop_front();
    }
    while (!que.empty() && que.back() < nums[i]) {
      que.pop_back();
    }
    que.push_back(nums[i]);
    result.push_back(que.front());
  }
  return result;
}

int main() {
  int n, k;
  std::cin >> n >> k;

  std::vector<int> nums(n, 0);
  for (int i = 0; i < n; i++) {
    std::cin >> nums[i];
  }
  std::vector<int> result = maxWindowSize(nums, k);

  for (auto i : result) {
    std::cout << i << " ";
  }
  return 0;
  // 8 3
  // 1 3 -1 -3 5 3 6 7
}