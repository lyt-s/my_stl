#include <iostream>
using namespace std;

/**
一个成员函数被定义为private属性，标志着其只能被当前类的其他成员函数(或友元函数)所访问。
而virtual修饰符则强调父类的成员函数可以在子类中被重写，因为重写之时并没有与父类发生任何的调用关系，故而重写是被允许的。

编译器不检查虚函数的各类属性。被virtual修饰的成员函数，不论他们是private、protect或是public的，都会被统一的放置到虚函数表中。
对父类进行派生时，子类会继承到拥有相同偏移地址的虚函数表（相同偏移地址指，各虚函数相对于VPTR指针的偏移），则子类就会被允许对这些虚函数进行重载。
且重载时可以给重载函数定义新的属性，例如public，其只标志着该重载函数在该子类中的访问属性为public，和父类的private属性没有任何关系！
*/
class WeatherBase {
 private:
  virtual void init();
};
class Rain : public WeatherBase {
 private:
  virtual void init();
};

class Base {
 private:
  virtual void func1() { cout << "Base::func1()" << endl; }
  virtual void func2() { cout << "Base::func2()" << endl; }
  virtual void func3() { cout << "Base::func3()" << endl; }
};

class Derived : public Base {
 public:
  void func2() override { cout << "Derived::func2()" << endl; }
  virtual void func4() { cout << "Derived::func4()" << endl; }
  void func5() { cout << "Derived::func5()" << endl; }
};

typedef void (*Fun)(void);

int main() {
  Derived obj;
  Base *ptrb = &obj;
  // ptrb->func2();  // err
  // ptrb->func4();	//err

  typedef void (*func)(void);

  cout << "obj_addr " << (&obj) << endl;
  cout << "vtbl_addr_addr " << (long *)(&obj) << endl;
  cout << "vtbl_addr "
       << "0x" << hex << *(long *)(&obj) << endl;
  cout << "fun1_addr_addr " << (long *)(*(long *)(&obj))
       << endl;  // output hexadecimal: cout << hex << num
  // cout<<"func1_addr "<<"0x"<<hex<<*(long *)(*(long*)(&obj))<<endl;
  func ptr1 = (func)(*(long *)(*(long *)(&obj)));
  ptr1();
  func ptr2 = (func)(*((long *)(*(long *)(&obj)) + 1));
  ptr2();
  func ptr3 = (func)(*((long *)(*(long *)(&obj)) + 2));
  ptr3();
  func ptr4 = (func)(*((long *)(*(long *)(&obj)) + 3));
  ptr4();
  // func ptr5=(func)(*((long *)(*(long *)(&obj))+4));	//seg fault, non-virutal
  // isnt included in vtbl ptr5();
}