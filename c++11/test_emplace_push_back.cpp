#include <iostream>
#include <vector>
using namespace std;
class A {
 public:
  A(int num) : n(num) { cout << "调用构造函数" << n << endl; }
  A(const A& a) : n(a.n) { cout << "调用拷贝构造函数:" << n << endl; }
  //	A(A && a):n(a.n) {
  //		cout << "调用移动拷贝构造函数"<< n << endl;
  //	}
  ~A() { cout << "调用析构函数" << n << endl; }

 private:
  int n;
};

int main(void) {
  vector<A> v1, v2;
  cout << "使用emplace_back:" << endl;
  v1.emplace_back(666);  // 支持直接传入参数构造
  // cout << "v1的size："<< v1.size() << endl;
  // cout << "v1的capacity："<< v1.capacity() << endl<<endl;
  cout << "使用push_back:" << endl;
  v2.push_back(999);
  cout << "开始析构---" << endl;
  return 0;
}

/*
 *
使用emplace_back:
调用构造函数666
使用push_back:
调用构造函数999
调用拷贝构造函数:999
调用析构函数999
开始析构---
调用析构函数999
调用析构函数666
*/