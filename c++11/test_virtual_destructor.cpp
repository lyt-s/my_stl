#include <iostream>
class Base {
 public:
  virtual ~Base() { std::cout << "Base destructor" << std::endl; }
};

class Derived : public Base {
 public:
  ~Derived() {
    std::cout << "Derived destructor";
    std::cout << std::endl;
  }
};

int main() {
  Base* base_ptr = new Derived();
  delete base_ptr;  // 首先调用Derived的析构函数，然后调用Base的析构函数
  return 0;
}
