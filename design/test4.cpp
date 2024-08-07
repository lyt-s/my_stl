#include <iostream>
using namespace std;
class A {
 private:
  int n1;
  int n2;
  const string m_name;

 public:
  A() : m_name("c") {
    n2 = 0;
    n1 = n2 + 2;
    // m_name = "A";
  }

  void Print() {
    cout << "n1:" << n1 << ", n2: " << n2 << "string :" << m_name << endl;
  }
};

int main() {
  A a;
  a.Print();

  return 1;
}