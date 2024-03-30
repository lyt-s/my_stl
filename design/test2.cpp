#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  int n, x, y;
  cin >> n >> x >> y;

  int word = 0, listen = 0, read = 0;

  word = (n + x - y) / 3;

  cout << word - x << " " << word + y << " " << word;
  return 0;
}
