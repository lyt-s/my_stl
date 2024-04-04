#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
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
  std::string line("[[1,3],[2,6],[8,10],[15,18]]");
  // getline(cin, line);
  stringstream ss(line);
  vector<int> num;
  vector<vector<int>> input;
  char ch;
  int number;
  while (ss >> ch) {
    if (ch == '[' || ch == ',') {
      continue;
    }
    if (ch == ']') {
      if (num.size() != 0) {
        input.push_back(num);
        num.clear();
      }

    } else {
      ss.unget();
      if (ss >> number) {
        num.push_back(number);
      }
    }
  }

  for (int i = 0; i < input.size(); i++) {
    std::cout << input[i][0] << " " << input[i][1] << " ";
  }
  vector<vector<int>> outputs;
  outputs = merge(input);

  for (int i = 0; i < outputs.size(); i++) {
    std::cout << outputs[i][0] << " " << outputs[i][1] << " ";
  }
  return 0;
}