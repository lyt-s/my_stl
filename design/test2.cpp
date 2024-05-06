#include "stdio.h"
class A {
 public:
  void f1() { printf("A::f1\n"); }

  virtual void f2() { printf("A::f2\n"); }
};
class B {
 public:
  virtual void f1() { printf("B::f1\n"); }

  virtual void f2() { printf("B::f2\n"); }
};
int main() {
  B b;
  A *p = (A *)&b;
  p->f1();
  p->f2();
  return 0;
}