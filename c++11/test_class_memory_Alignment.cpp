#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
struct A {
  int x;
} A;

class Base {
 public:
  Base() : x(0){};
  virtual void print() { printf("print my value %d\n", x); }

 private:
  int x;
  static std::string s_x;

  // int y;
  double value;
};

class Base2 {
  virtual void print_2() { printf("print my value %d\n", x); }

 private:
  int x = 0;
  double value;
};

std::string Base::s_x = "lz";

class Driver : public Base, public Base2 {
 public:
  virtual void print() { printf("print my value %d\n", xl); }

 private:
  // string 32大小
  // std::string name;
  int xl = 3;
  char a;
  int m_y;
};

class Driver2 : public Base {
 public:
  virtual void print() {
    printf("print my value %d, name %s \n", xl, m_name.c_str());
  }

 private:
  std::string m_name = "asd";
  int xl = 4;
};
int main() {
  struct A a;
  a.x = 12345, A.x = 123;
  std::cout << a.x << " " << A.x << std::endl;

  Base base;
  // 指针大小为8, 所以 base 为 16
  std::cout << "base::sizeof = " << sizeof(base) << std::endl;

  Driver driver;
  // 24
  std::cout << "driver::sizeof = " << sizeof(driver) << std::endl;

  Base *base2 = new Driver();
  std::vector<Base *> vec;
  vec.push_back(base2);

  Base *base3 = new Driver2();
  vec.push_back(base3);
  vec[0]->print();
  vec[1]->print();

  // 指针大小为8
  std::cout << "*base2.sizeof = " << sizeof(&base2) << std::endl;
  std::cout << "string.sizeof = " << sizeof(std::string) << std::endl;
  return 0;
}