#include <stdio.h>
class Point {
 public:
  Point() { m_nPointCount++; }
  ~Point() { m_nPointCount--; }
  static void output() { printf("%d\n", m_nPointCount); }

 private:
  static int m_nPointCount;
};

int Point::m_nPointCount = 0;

int main() {
  Point pt;
  pt.output();
  Point::output();
}