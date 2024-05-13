#include <stdlib.h>

#include <iostream>
using namespace std;

class Foo {
 public:
  Foo() : id(0), name("null") {
    cout << "Ctor" << endl;
    cout << id << "-" << name << endl;
  }

  Foo(int id, string name) : id(id), name(name) {
    cout << "Ctor" << endl;
    cout << id << "-" << name << endl;
  }

  ~Foo() { cout << "Dtor" << endl; }

  // 如果在类中有重载的话编译器会调用以下的重载函数而不用全局函数
  // static void* operator new(size_t);
  // static void operator delete(void*, size_t);
  void* operator new(size_t);
  void operator delete(void*, size_t);

 private:
  int id;
  string name;
};

void* Foo::operator new(size_t size) {
  cout << "MyOperatorNew" << endl;
  return malloc(size);
}

void Foo::operator delete(void* ptr, size_t size) {
  cout << "MyOperatorDelete" << endl;
  free(ptr);
}

int main() {
  Foo* foo = new Foo(2, "dae");
  delete foo;
  return 0;
}