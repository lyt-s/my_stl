#include <cstdint>
#include <cstring>
#include <iostream>
#include <memory>
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

void GetMemory(char*& p) { p = (char*)malloc(100); }

void Test(void) {
  char* str = NULL;
  GetMemory(str);
  strcpy(str, "hello world");
  printf(str);
}

void Func(char str[100]) { std::cout << sizeof(str); }
int main() {
  uint16_t wId = 2;
  uint16_t* p1 = &wId;
  uint32_t* p2 = (uint32_t*)p1;
  uint32_t dwId = *p2;
  std::cout << dwId << '\n';
  test2();
  std::shared_ptr<int> x;

  char str[] = "Hello";
  char* p = str;
  int n = 10;
  // 32 位
  std::cout << sizeof(str);  // 6
  std::cout << sizeof(p);    // 4
  std::cout << sizeof(n);    // 4
  // void* p2 = malloc(100);
  char str2[100];
  Func(str2);
  std::cout << sizeof(p2);  // 4
  Test();

  return 0;
}