#include <iostream>
#include <queue>
#include <vector>
using namespace std;

class A {
 public:
  A() = default;
  A(const A& a) { cout << "A& called" << endl; }
  A(A&& a) { cout << "A&& called" << endl; }
};
class B {
 public:
  B() = default;
  B(const B& a) { cout << "B& called" << endl; }
  // B(B&& a) { cout << "B&& called" << endl; }
};

class C {
 public:
  A a;
  B b;
  string str;
  vector<int> vec;
};
int main() {
  C q;
  q.str = "123456";
  q.vec.resize(100);
  C w(std::move(q));

  int* ptr = new int(42);
  delete ptr;  // 释放内存

  // 此时，ptr成为一个空悬指针，因为它指向的内存已经被释放
  std::cout << *ptr << std::endl;  // 访问空悬指针，可能导致未定义行为

  int* ptr2 = nullptr;

  std::cout << *ptr2 << std::endl;
  return 0;
}
