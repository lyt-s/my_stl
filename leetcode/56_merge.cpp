#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

std::vector<std::vector<int>> merge(std::vector<std::vector<int>> &inputs) {
  vector<vector<int>> result;
  std::sort(inputs.begin(), inputs.end());

  for (int i = 0; i < inputs.size();) {
    int t = inputs[i][1];
    int j = i + 1;
    while (j < inputs.size() && inputs[j][0] <= t) {
      t = std::max(t, inputs[j][1]);
      j++;
    }
    result.push_back({inputs[i][0], t});
    i = j;
  }
  return result;
}

int main() {
  int n, x, y;
  vector<vector<int>> inputs;
  std::cin >> n;
  while (n--) {
    cin >> x >> y;
    // cout << x << " " << y << endl;
    inputs.push_back({x, y});
  }

  // for (int i = 0; i < inputs.size(); i++) {
  //   std::cout << inputs[i][0] << " " << inputs[i][1] << " ";
  // }
  vector<vector<int>> outputs;
  outputs = merge(inputs);

  for (int i = 0; i < outputs.size(); i++) {
    std::cout << outputs[i][0] << " " << outputs[i][1] << " ";
  }
  return 0;
}