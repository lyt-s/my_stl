#include <iostream>
class E {
 public:
  virtual void func(int i = 0) { std::cout << "E::func()\t" << i << "\n"; }
};
class F : public E {
 public:
  virtual void func(int i = 1) { std::cout << "F::func()\t" << i << "\n"; }
};

void test2() {
  F* pf = new F();
  E* pe = pf;
  pf->func();  // F::func() 1  正常，就该如此；
  pe->func();  // F::func() 0
               // 哇哦，这是什么情况，调用了子类的函数，却使用了基类中参数的默认值！
}

int main() {
  test2();
  return 0;
}