#include <cmath>
#include <iostream>
using namespace std;
bool isprime(int input) {
  if (input < 2) {
    return false;
  }
  for (int i = 2; i <= sqrt(input); i++) {
    if (input % i == 0) {
      return false;
    }
  }
  return true;
}
int gcd(int a, int b) {
  while (b) {
    int tmp = b;
    b = a % b;
    a = tmp;
  }
  return a;
}
int main() {
  int t{};
  cin >> t;
  for (int i = 0; i < t; i++) {
    int n{};
    cin >> n;
    for (int j = 2; j <= n; j++) {
      int tmp = gcd(n, j);
      if (isprime(tmp)) {
        cout << j << endl;
        break;
      }
    }
  }
  return 0;
}
// 64 位输出请用 printf("%lld")