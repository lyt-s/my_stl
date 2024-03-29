#include <iomanip>
#include <iostream>

using namespace std;

int main() {
  double n;
  cin >> n;

  double p = (2.0 / n) * (1 / (n - 1));

  cout << fixed << std::setprecision(10) << p;

  return 0;
}