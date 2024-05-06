#include <iostream>

//----------------------------------------------------------------

// struct A {
//   int val = 42;
//   virtual void fun() { std::cout << "A::fun" << std::endl; }
// };
// struct B : public A {
//   void fun() override { std::cout << "B::fun" << std::endl; }
// };
// struct C : public A {
//   void fun() override { std::cout << "C::fun" << std::endl; }
// };
// struct D : public B, public C {
//   // void fun() override { std::cout << "D::fun" << std::endl; }
// };
// int main(int argc, char const *argv[]) {
//   D d;
//   // std::cout << d.val
//   //           << std::endl;  // 编译失败，不知道调用从哪个类中继承的val变量
//   // 解决的办法有两种，一种是在调用符之前加上父类限定符：
//   std::cout << d.B::val << std::endl;
//   // d.fun();  // 编译失败，不知道调用从哪个类中继承的fun函数
//   d.C::fun();

//   // 但这里并没有解决数据冗余的问题，因为D中有B和C，
//   // 而B和C各有一个虚表和一个int类型的成员变量，所以sizeof(D) 的大小是32
//   // （x86_64架构，考虑到内存对齐）。
// }

// ----------------------------------------------------------------
struct A {
  int val = 42;
  virtual void fun() { std::cout << "A::fun" << std::endl; }
};
struct B : virtual public A {
  void fun() override { std::cout << "B::fun" << std::endl; }
};
struct C : virtual public A {
  void fun() override { std::cout << "C::fun" << std::endl; }
};
struct D : public B, public C {
  void fun() override { std::cout << "D::fun" << std::endl; }
};
int main(int argc, char const *argv[]) {
  D d;
  // 此时在对象d中，只包含了一个val和两个虚指针，成员变量的冗余问题得到解决。
  std::cout << d.val << std::endl;  // 42
  d.fun();                          // D::fun
}