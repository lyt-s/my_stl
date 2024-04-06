#include <stdio.h>

#include <iostream>

/**
volatile
意思是易变的，是一种类型修饰符，在C/C++中用来阻止编译器因误认某段代码无法被代码本身所改变，而造成的过度优化。编译器每次读取
volatile 定义的变量时，都从内存地址处重新取值。

这里就有点疑问了，难道编译器取变量的值不是从内存处取吗？

并不全是，编译器有时候会从寄存器处取变量的值，而不是每次都从内存中取。
因为编译器认为变量并没有变化，所以认为寄存器里的值是最新的，另外，
通常来说，访问寄存器比访问内存要快很多，编译器通常为了效率，可能会读取寄存器中的变量。
但是，变量在内存中的值可能会被其它元素修改，比如：硬件或其它线程等。
*/

int main() {
  volatile const int value = 10;
  int *ptr = (int *)&value;

  printf("初始值 : %d \n", value);

  *ptr = 100;
  printf("修改后的值 : %d \n", value);

  // 添加 volatile时，输出 10 10
  // 添加后 10 100
  long a = (long)(((int *)0) + 4);
  std::cout << a << std::endl;
  return 0;
}