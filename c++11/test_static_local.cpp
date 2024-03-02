#include <iostream>
#include <string>
#include <vector>

void funC() { static int a = 1; }

int main() {
  funC();
  return 0;
}