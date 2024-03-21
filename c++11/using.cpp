#include <iostream>
#include <map>
class Base {
 protected:
  int bn1;
  int bn2;
};

class Derived : private Base {
 public:
  using Base::bn1;
};

class DerivedAgain : public Derived {};

namespace n1 {
int n1_member = 10;
int m = 11;
}  // namespace n1

int m = 12;

int main() {
  // 1.-----------------------------------------------------------
  {
    using std::map;
    map<int, std::string> the_map;  // ok
  }
  // map<int, std::string> the_map2;  // error
  // 2.-----------------------------------------------------------
  Derived d;
  DerivedAgain da;
  d.bn1 = 1;
  // d.bn2 = 2;   // error, 'bn2' is a private member of 'Base'
  da.bn1 = 3;  // ok
  std::cout << d.bn1 << std::endl;
  // 3.命名空间------------------------------------------------
  using namespace n1;
  std::cout << n1_member << std::endl;
  // std::cout<<m<<std::endl;  //error 命名冲突
  std::cout << ::m << std::endl;

  int m = 13;  // ok, 局部变量屏蔽命名空间变量
  std::cout << m << std::endl;
  return 0;
}