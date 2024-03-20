#include <iostream>
#include <queue>
using namespace std;
int main() {
  // 对于基础类型 默认是大顶堆 降序队列
  priority_queue<int> a;
  // 等同于 priority_queue<int, vector<int>, less<int> > a;

  priority_queue<int, vector<int>, greater<int>> c;  // 这样就是小顶堆,升序队列
  priority_queue<string> b;

  for (int i = 0; i < 5; i++) {
    a.push(i);
    c.push(i);
  }
  std::cout << "大顶堆" << std::endl;
  while (!a.empty()) {
    cout << a.top() << ' ';
    a.pop();
  }
  std::cout << "小顶堆" << std::endl;

  while (!c.empty()) {
    cout << c.top() << ' ';
    c.pop();
  }
  cout << endl;

  b.push("abc");
  b.push("abcd");
  b.push("cbd");
  while (!b.empty()) {
    cout << b.top() << ' ';
    b.pop();
  }
  cout << endl;
  return 0;
}
