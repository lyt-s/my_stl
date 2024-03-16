// #include <iostream>
// #include <string>
// #include <vector>

// void funC() { static int a = 1; }

// int main() {
//   funC();
//   return 0;
// }

#include <iostream>

using namespace std;

const int N = 100010;
int a[N];
int s2[N], s5[N];

int main() {
  int n, k;
  cin >> n >> k;
  for (int i = 1; i <= n; i++) cin >> a[i];

  // 2 5
  for (int i = 1; i <= n; i++) {
    int t = a[i];
    while (t % 2 == 0) {
      t /= 2;
      s2[i]++;
    }
    s2[i] = s2[i - 1] + s2[i];

    t = a[i];
    while (t % 5 == 0) {
      t /= 5;
      s5[i]++;
    }
    s5[i] = s5[i - 1] + s5[i];
  }

  int res = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j++) {
      int remain_2 = s2[i - 1] + s2[n] - s2[j];
      int remain_5 = s5[i - 1] + s5[n] - s5[j];

      if (remain_2 >= k && remain_5 >= k) {
        res++;
        cout << i << ' ' << j << endl;
      }
    }
  }

  cout << res << endl;
}
