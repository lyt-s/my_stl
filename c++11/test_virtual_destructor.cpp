#include <iostream>
#include <iterator>
#include <string>
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

class CrazyInt {
  int v;
  std::string m_name = "lyt";
  int m_old = 18;

 public:
  CrazyInt(int i) : v(i) {}
  operator int() const {
    std::cout << m_name << " 年龄：" << m_old << std::endl;
    if (v == 0) return false;
    return true;
  }  // conversion from CrazyInt to int
};

void print_class(int a) { std::cout << a << std::endl; }

int num_1(int a) {
  int res = 0;
  int b = a;
  while (b) {
    if (b % 2) {
      res++;
    }
    b = b >> 1;
  }
  return res;
}
int hammingWeight(int n) {
  int res = 0;
  while (n) {
    res += n & 1;
    n >>= 1;
  }
  return res;
}
int main() {
  int x = 50;
  int y = hammingWeight(x);

  std::cout << y << std::endl;
  // CrazyInt b = 55;
  // print_class(999);  // prints 999
  // print_class(b);    // prints 55
}

// int main() {
//   Base* base_ptr = new Derived();
//   delete base_ptr;  // 首先调用Derived的析构函数，然后调用Base的析构函数
//   return 0;
// }
