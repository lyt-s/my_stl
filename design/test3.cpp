#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

vector<int> findFValues(const vector<int>& nums) {
  vector<int> fValues;
  int maxElement = *max_element(nums.begin(), nums.end());
  for (int i = 0; i < nums.size(); ++i) {
    fValues.push_back(max(maxElement, nums[i] * 2));
  }
  return fValues;
}

int main() {
  int n;
  cin >> n;
  vector<int> nums(n);
  for (int i = 0; i < n; ++i) {
    cin >> nums[i];
  }

  vector<int> fValues = findFValues(nums);
  for (int i = 0; i < n; ++i) {
    cout << fValues[i];
    if (i < n - 1) {
      cout << " ";
    }
  }
  return 0;
}