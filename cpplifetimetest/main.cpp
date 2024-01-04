#include <cstdio>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "cppdemangle.h"

struct Test {
  char buf[1024];
  std::string name;
  explicit Test(std::string name_ = "") : name(std::move(name_)) {
    // puts("===");
    printf("Test() %s\n", name.c_str());
    // puts("===");
  }
  Test(Test &&that) noexcept : name(that.name) {
    // that -> this
    that.name = "null";
    name += "_move";
    printf("Test(Test &&) %s\n", name.c_str());
  }
  Test &operator=(Test &&that) noexcept {
    name += "_move";
    printf("Test &operator=(Test &&) %s\n", name.c_str());
    name = that.name;
    return *this;
  }
  Test(Test const &that) : name(that.name) {
    name += "_copy";
    printf("Test(Test const &) %s\n", name.c_str());
  }
  Test &operator=(Test const &that) {
    name = that.name;
    name += "_copy";
    printf("Test &operator=(Test const &) %s\n", name.c_str());
    return *this;
  }
  ~Test() noexcept { printf("~Test() %s\n", name.c_str()); }
};

// void func(Test t) { puts("func"); }

/* void funcref(Test &t) { */
/*     puts("func"); */
/* } */

std::string const &func(std::string const &s) { return s; }

void func(std::unique_ptr<Test> t) { puts("func"); }

// 主类型 std::string
// 弱引用类型 std::string_view、const char *
// 主类型 std::vector<T>
// 弱引用类型 std::span<T>、(T *, size_t)
// 主类型 std::unique_ptr<T>
// 弱引用类型 T *
// 主类型 std::shared_ptr<T>
// 弱引用类型 std::weak_ptr<T>、T *

// void func0() {
//   //
//   //   int *p = new int;  // std::unique_ptr<int> p(new int);
//   //   int *p2 = p;
//   //   delete p;

//   std::shared_ptr<int> p = std::make_shared<int>();
//   std::shared_ptr<int> p2 = p;
//   std::weak_ptr<int> wp = p;  // 不影响引用计数，就好比房子里的幽灵
//   wp.lock();  // 将幽灵变为真人，如何房子存在，则可以进入，不在则不进入
//   p2.reset();  // todo
//   //   delete p2;  // dubug 模式下 会报错，double free , 可以改为unique_ptr
// }

//  int *p --->  p 掉出了这个括号会释放，*p 并没有释放，
// p只是一个地址，*p才是其中的内容，就好比房产证和房子。p(房产证)
// 会自动销毁 ，释放的是指针而不是指针指向的东西
// 申请了房地产，但是销毁只是销毁房产证,---> delete p 相当于销毁房子

std::string split(std::string s, char c) {
  auto pos = s.find(c);
  if (pos == std::string::npos) {
    return s;
  }
  return s.substr(0, pos);
}

void func(Test &&t) { puts("func(Test &&t)"); }

void func(Test const &t) {
  puts("func(Test const &t)");
  // puts("===");
}  // 在这里将传入的 t 析构掉

// 这个函数，参数在传入到func时，会重新拷贝一份t，增加一次析构
// 上面的则不会拷贝，少一次拷贝和析构，两个函数只能出现一个，会有冲突
void func3(Test t) {
  //
  puts("func(Test t)");
}

void func(int i, int j) { puts("func(int i, int j)"); }

// 万能引用，转发
#define FWD(x) std::forward<decltype(x)>(x)
template <typename... T>
void func2(T &&...t) {
  func(FWD(t)...);
}

// void func() {
//   {
//     puts("===");
//     Test t("t");
//     { Test t2("t2"); }
//     puts("===");
//   }  // t.~Test() 自动调用析构函数 , 加括号后析构提前,作用域
//   puts("---");
// }  // t.~Test() 自动调用析构函数

// std::string const &func_test(std::string s) {
//   // 会将 hello 拷贝一份 --s
//   return s;  // s 出作用域时自动析构,
// }

std::string const &func_test(std::string const &s) {
  // 会将 hello 拷贝一份 --s
  return s;  // s 出作用域时自动析构
}

std::vector<std::function<void()>> g_funcs;

void fun(auto f) { g_funcs.emplace_back(std::move(f)); }

void bao() {
  for (auto &f : g_funcs) {
    f();
  }
}

void foo() {
  // int i = 1;
  std::shared_ptr<int> i(new int);

  fun([i]() { printf("1_i = %d\n", (*i)++); });
  fun([i]() { printf("2_i = %d\n", (*i)++); });
}

int main() {
  // lambda 函数合适传& =
  // 这里会出错， 将 i  推到了全局， 其实已经析构
  // i 来计数，lambda 和shared_ptr 结合使用
  foo();
  // [&]这里会乱打印i, = 会正常打印
  bao();

  // 测试 5
  // 1.
  // auto ret = func_test(std::string("hello"));
  // // std::cout << *ret << std::endl;
  // printf("%s\n", ret.c_str());

  // segmentation fault 这里 s, 出作用域 时， 会自动析构 --->  std::string const
  // &func_test(std::string s) 情况下

  // 2.
  // auto s = std::string("test");
  // auto ret = &func_test(s);  // 正常的 ret 和 s 是同一个对象
  // printf("%s\n", ret->c_str());
  // 3.
  // std::string const *ret;
  // {
  //   auto s = std::string("test");
  //   ret = &func_test(s);  // s 出了作用域，析构。但是 ret 持有 s的指针
  //   //  未定义行为 内存泄漏
  //   // ，变量未初始化，调试模式未初始化变量为0
  //   // ，但是发布模式未初始化变量则有可能不是0. msvc
  // }
  // // std::cout << *ret << std::endl;
  // printf("%s\n", ret->c_str());  // Release 出现异常 Debug模式正常

  // 4. 在 func_test(const std::string & s)下，release 和 debug
  // 模式下都显示正常，但是存在泄露
  // 在返回时，它被以引用的形式返回。这意味着在main函数中，ret变量实际上引用了一个临时std::string对象，该对象是由std::string("hello")复制构造而来。
  // 其实 hello, 在 " ; "处就析构了，有一个小字符优化，
  // 有潜在隐患,肯定有问题，一定已经释放掉了。
  // auto ret = func_test(std::string(
  //     "helloppppppppppppppppppppppppppppppppppppppppppppppppppppppp"
  //     "pppffffffffffffffffffffffffffffffffffffffsssssssssssssssssssf"));
  // printf("%s\n", std::string("asdaklsfasnbdfiasdjiasd").c_str());
  // printf("%s\n", ret.c_str());

  // 测试 1
  // func();
  // 测试 2
  // Test t("t");  // 这个传入下面的函数时，才会在main结束后析构。
  // func2(Test("t")), puts("---");
  // // 此语句和下面括号内的内容等价,只不过就是调用的构造函数不同
  // puts("{-----------}");
  // {
  //   Test t1("t1");
  //   func2(t1);
  //   puts("---");
  // }
  // // 出 } 后，t1 会在此进行析构
  // puts("===");
  // // 当在main 定义  Test t("t");  会在main语句结束后，将Test t 析构掉

  // 测试 3
  // Test t("t");
  // func3(t), puts("===");  // func(test t) 时，会多一次拷贝和析构,
  //                         // 上面的和括号中的语句等价
  // {
  //   Test t_copy(t);
  //   func(t_copy), puts("===");
  // }
  // puts("===");

  // 测试 4 move
  // Test t("t");  // 调用Test的构造函数 ，会在main } 处析构，delete 空指针
  // func(std::move(t)), puts("===");  // 调用 func(Test &&t)
  // {
  //   Test t_move(std::move(t));  // 调用Test的移动构造函数
  //   // 移动就是创建了一个一模一样的对象，仅此而已，还是会再次析构t
  //   //  此时 t 已经没了
  //   func(t_move), puts("===");
  // }

  //  移动赋值和移动构造函数的区别
  // 每个构造函数对应一个析构，赋值函数则不会
  // func2(3, 4);
  /* t = t2; */
  /* Test t2(std::move(t)); */
  /* t2 = std::move(t); */

  // 测试 6
  // 这里移动的是智能指针本身，不是指针指向的内容
  // 默认unique_ptr不会调用调用test的拷贝和移动构造函数
  // std::unique_ptr<Test> t(new Test("t"));
  /*所以move 时，不会调用移动构造函数，这里移动的是，指针
  移动的只是房产证，不是房子
  不能拷贝
  */
  // func(std::move(t));

  /* auto ret = func(std::string("hello")); */
  /* printf("%s\n", ret.c_str()); */
  /* Test t("t"); */
  /* func(std::move(t)), puts("==="); */
  /* { Test t_move(std::move(t)); funcref(t_move), puts("==="); } */
  /* puts("---"); */
  return 0;
}