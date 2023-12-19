#include "Vector.hpp"

int main() {
  // 实现 operator[] size()
  auto print_list = [&](Vector<int> &vector) {
    for (size_t i = 0; i < vector.size(); ++i) {
      printf("arr[%zd] = %d\n ", i, vector[i]);
    }
  };

  auto print_string_list = [&](Vector<char *> &str) {
    for (size_t i = 0; i < str.size(); ++i) {
      printf("arr[%zd] = %s\n ", i, str[i]);
    }
  };

  auto push_list = [&](Vector<int> &vector) {
    for (size_t i = 0; i < 16; ++i) {
      vector.push_back(i);
    }
  };

  // // test  默认构造函数
  Vector<int> vec;
  // 有参构造函数
  std::cout << "vec2 ---------------------------------" << std::endl;
  Vector<int> vec2(3, 8);
  print_list(vec2);
  // 拷贝构造  实现深拷贝 --如果没有就会
  // free(): double free detected in tcache 2
  std::cout << "vec3 ---------------------------------" << std::endl;
  Vector<int> vec3(vec2);
  print_list(vec3);
  std::cout << "vec4 ---------------------------------" << std::endl;
  // 会调用 拷贝构造函数
  Vector<int> vec4 = vec3;
  vec4[2] = 0;
  print_list(vec4);
  std::cout << "arr ---------------------------------" << std::endl;
  Vector<int> arr;
  // 会调用拷贝赋值函数， 注意 和 Vector arr = vec4 区别
  arr = vec4;
  print_list(arr);
  std::cout << "bar ---------------------------------" << std::endl;
  // 移动构造函数
  Vector<int> bar(std::move(vec2));
  print_list(bar);
  std::cout << "car ---------------------------------" << std::endl;
  // 移动构造函数
  Vector<int> car = std::move(bar);
  print_list(car);
  std::cout << "vec4 ---------------------------------" << std::endl;
  // 会调用，移动赋值函数， 注意和上面的区别
  vec4 = std::move(vec3);
  print_list(vec4);
  //   //   todo
  //   initializer list
  // error 初始化失败，出现段错误，是因为
  // initializer_list构造函数在调用别的构造函数时写在了{}内部，
  // 应该写在 : 后面 --->
  //    Vector(std::initializer_list<T> ilist)
  //   : Vector(ilist.begin(), ilist.end()) {}
  std::cout << "vec5 ---------------------------------" << std::endl;
  Vector vec5{1, 2, 3, 4, 5, 6};
  std::cout << vec5[1] << "\n";
  print_list(vec5);

  // test clear() push_back() resize() pop_back()
  //   Vector vec(4, 3);
  //   print_list(vec);
  //   vec.clear();
  //   print_list(vec);
  //   std::cout << "vec.size() = " << vec.size() << std::endl;
  //   push_list(vec);
  //   print_list(vec);
  //   std::cout << "vec.resize(8) = " << std::endl;
  //   vec.resize(8);
  //   print_list(vec);
  //   std::cout << "vec.resize(16) = " << std::endl;
  //   vec.resize(16);
  //   print_list(vec);
  //   std::cout << "vec.resize(16,1) = " << std::endl;
  //   vec.resize(16, 1);
  //   print_list(vec);
  //   vec.resize(8);
  //   vec.resize(17, 1);
  //   vec[16] = 2;
  //   print_list(vec);
  //   vec.pop_back();
  //   print_list(vec);

  // test shrink_to_fit capacity()
  //   Vector bar;
  //   bar.reserve(100);
  //   bar.resize(100);
  //   std::cout << "Capacity of a 100-element vector is " << bar.capacity() <<
  //   '\n'; bar.resize(50); std::cout << "Capacity after resize(50) is " <<
  //   bar.capacity() << '\n'; bar.shrink_to_fit(); std::cout <<
  //   "Capacity_after_shrink_to_fit() is" << bar.capacity() << '\n';
  //   bar.clear();
  //   std::cout << "Capacity after clear() is " << bar.capacity() << '\n';
  //   bar.shrink_to_fit();
  //   std::cout << "Capacity after shrink_to_fit() is " << bar.capacity() <<
  //   '\n';

  //   // test assign() erase()
  // Vector<int> vec;
  // Vector<int> vec2;
  // push_list(vec2);
  // vec.assign(4, 4);
  // print_list(vec);
  // vec.assign(vec2.begin(), vec2.end());
  // print_list(vec);
  // vec.erase(vec.begin());
  // print_list(vec);
  // vec.erase(vec.begin(), vec.begin() + 3);
  // print_list(vec);

  // Vector<char *> lines;
  // lines.push_back((char *)"hello");
  // lines.push_back((char *)"world");
  // print_string_list(lines);

  return 0;
}