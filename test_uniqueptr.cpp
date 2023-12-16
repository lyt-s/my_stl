#include <cstdio>
#include <iostream>
#include <vector>

#include "UniquePtr.hpp"

struct MyClass {
  int a, b, c;
};

struct Animal {
  virtual void speak() = 0;
  virtual ~Animal() = default;
};

struct Dog : Animal {
  int age;

  Dog(int age_) : age(age_) {}

  virtual void speak() { printf("Bark! I'm %d Year Old!\n", age); }
};

struct Cat : Animal {
  int &age;

  Cat(int &age_) : age(age_) {}

  virtual void speak() { printf("Meow! I'm %d Year Old!\n", age); }
};

int main() {
  std::vector<UniquePtr<Animal>> zoo;
  int age = 3;
  zoo.push_back(makeUnique<Cat>(age));
  zoo.push_back(makeUnique<Dog>(age));
  for (auto const &a : zoo) {
    a->speak();
  }
  age++;
  for (auto const &a : zoo) {
    a->speak();
  }

  union EndianTest {
    int intValue;
    char byteArray[sizeof(int)];
  };

  EndianTest test;
  test.intValue = 1;

  if (test.byteArray[0] == 1) {
    std::cout << "Little Endian" << std::endl;
  } else {
    std::cout << "Big Endian" << std::endl;
  }

  return 0;
}