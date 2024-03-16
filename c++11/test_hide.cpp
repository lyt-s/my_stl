#include <iostream>

class Base {
 public:
  void display() { std::cout << "Base class" << std::endl; }
};

class Derived : public Base {
 public:
  void display(int val) {
    std::cout << "Derived class val :" << val << std::endl;
  }
};

int main() {
  Derived derivedObj;
  derivedObj.display(2);  // 输出 "Derived class"

  Base* basePtr = &derivedObj;
  basePtr->display();  // 输出 "Base class"，被隐藏的函数

  return 0;
}