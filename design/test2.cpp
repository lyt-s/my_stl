// #include <stdio.h>

// #include <cstddef>
// #include <iostream>
// #include <iterator>
// #include <ostream>

// class Test {
//  public:
//   void HelloWorld() { std::cout << "Hello World" << std::endl; }
// };

// struct T {
//   char a;
//   int *d;
//   int b;
//   int c : 16;
//   double e;
// };
// int main(void) {
//   char str[20] = "ABCDEFG";
//   int k1 = 10;
//   int k2 = 20;

//   // auto func = [str, k1, &k2]() {
//   //   printf("str:%s, k1:%d, k2:%d\n", str, k1, k2);
//   // };
//   // func();
//   // str[2] = 'D';
//   // k1 = 20;
//   // k2 = 10;

//   // func();
//   // T *p;
//   // std::cout << sizeof(p->a) << std::endl;

//   // char a[] = "12345";
//   // char b[] = {'1', '2', '3', '4', '5'};
//   // bool x = (a[0] == b[0]);
//   // std::cout << x << sizeof(a) << sizeof(b) << std::endl;

//   // int a[] = {1, 2, 3};
//   // int *e = &a[0];
//   // int *p = e;
//   // p = &a[1];
//   // *p = ++(a[0]);
//   // *(p + 1) = 1;

//   // std::cout << a[0] << " " << a[1] << " " << a[2] << " " << std::endl;

//   // Test *pHello = NULL;
//   // pHello->HelloWorld();

//   // int32_t times[10][100] = {0};
//   // std::cout << sizeof(times) << std::endl;

//   int a = 3, b = 4, c = 5;
//   std::cout << a && b;
//   std::cout << !((a < b) && !c || 1);

//   std::cout << a || b + c && b - c;
//   std::cout << sizeof(char **);
//   int *p = new int(8);

//   // unsigned int size = 10;
//   // while (size >= 0) {
//   //   printf("%d\n", size);
//   //   size--;
//   // }

//   int num1 = 60000;
//   short num2 = (short)(num1);
//   while (num2 > 0) {
//     printf("%d\n", num2);
//     --num2;
//   }
//   return 0;
// }

#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

// 计算两点之间的曼哈顿距离（x和y坐标的差的绝对值之和）
int countDis(int x, int y) {
  if (x < 0) {
    x = -x;
  }
  if (y < 0) {
    y = -y;
  }
  return x + y;
}

// 获得连接所有点的最短路径长度
int getMinLen(vector<vector<int>>& points) {
  int ans = 0;
  vector<bool> rep(points.size(), false);
  vector<vector<int>> q;
  q.push_back({0, 0});
  while (!q.empty()) {
    vector<int> curr = q.front();
    q.erase(q.begin());
    int min = INT_MAX;
    int minD = 0;
    int x = 0, y = 0;
    for (int k = 0; k < points.size(); ++k) {
      if (rep[k]) {
        continue;
      }
      int dis = countDis(curr[0] - points[k][0], curr[1] - points[k][1]);
      if (min > dis) {
        // 如果到这个点的距离是最短的，记录这个点
        min = dis;
        minD = k;
        x = points[k][0];
        y = points[k][1];
      }
    }
    if (x == 0 && y == 0) {
      break;
    }
    rep[minD] = true;
    ans += min;
    q.push_back({x, y});
  }
  cout << ans << endl;
  return ans;
}

int main() {
  // 测试代码
  vector<vector<int>> points{{0, 5}, {1, 1}};  // 初始化点的坐标
  getMinLen(points);
  return 0;
}