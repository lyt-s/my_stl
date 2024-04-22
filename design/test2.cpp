#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

// Helper function to calculate all possible subset sums and their count modulo
// m.
unordered_map<int, int> subsetSums(vector<int>& nums, int m) {
  unordered_map<int, int> sums = {{0, 1}};  // include empty subset
  for (int num : nums) {
    unordered_map<int, int> newSums(sums);
    for (auto& sum : sums) {
      int newSum = (sum.first + num) % m;
      newSums[newSum] = newSums[newSum] + sum.second;
    }
    sums.swap(newSums);
  }
  return sums;
}

int main() {
  int n, A, B;
  cin >> n >> A >> B;
  vector<int> arr(n);
  for (int i = 0; i < n; ++i) {
    cin >> arr[i];
  }

  vector<int> firstHalf(arr.begin(), arr.begin() + n / 2);
  vector<int> secondHalf(arr.begin() + n / 2, arr.end());

  // Calculate subset sums for both halves modulo A and B
  unordered_map<int, int> firstHalfSumsA = subsetSums(firstHalf, A);
  unordered_map<int, int> secondHalfSumsB = subsetSums(secondHalf, B);

  // Count the number of compatible pairs of subset sums
  long long count = 0;
  for (auto& fa : firstHalfSumsA) {
    count += (long long)fa.second * secondHalfSumsB[(B - fa.first % B) % B];
  }

  unordered_map<int, int> firstHalfSumsB = subsetSums(firstHalf, B);
  unordered_map<int, int> secondHalfSumsA = subsetSums(secondHalf, A);

  for (auto& sa : secondHalfSumsA) {
    count += (long long)sa.second * firstHalfSumsB[(A - sa.first % A) % A];
  }

  // Subtract the cases when all are painted in one color since they are counted
  // twice
  count -= firstHalfSumsA[0] * secondHalfSumsA[0];
  count -= firstHalfSumsB[0] * secondHalfSumsB[0];

  // Finally, add the cases when all are painted in one color
  count += firstHalfSumsA[0] + secondHalfSumsA[0] -
           2;  // All black - subtracting extra empty case
  count += firstHalfSumsB[0] + secondHalfSumsB[0] -
           2;  // All white - subtracting extra empty case

  cout << count << endl;

  return 0;
}