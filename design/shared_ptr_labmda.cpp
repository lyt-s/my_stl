#include <functional>
#include <iostream>
#include <memory>
#include <ostream>
class A {
 private:
  int m_val = 0;

 public:
  ~A() { std::cout << " ~A" << std::endl; }
  void print() { std::cout << m_val << std::endl; }
};

void example1() {
  std::shared_ptr<A> ptr(new A);
  {
    // 使用函数对象捕获智能指针
    auto functor = [ptr]() { std::cout << "a" << std::endl; };
    functor();
  }

  std::cout << "Ref count: " << ptr.use_count()
            << std::endl;  // Output: Ref count: 2
}

void example2() {
  std::shared_ptr<int> ptr2(new int(42));

  // 使用 std::function 捕获智能指针
  std::function<void()> lambda = [ptr2]() { std::cout << *ptr2 << std::endl; };
  lambda();

  // 引用计数会降为 0,因为 lambda 是临时对象
  std::cout << "Ref count: " << ptr2.use_count()
            << std::endl;  // Output: Ref count: 1
}

int main() {
  example1();

  return 0;
}

// #include <functional>
// #include <iostream>
// #include <memory>

// int main() {
//   auto sp = std::make_shared<int>(10);  // sp的引用计数为1

//   std::cout << "sp initial use_count: " << sp.use_count() << std::endl;

//   // Lambda表达式捕获sp的拷贝
//   // 在lambda里面使用拷贝，引用计数会增加
//   auto lambda_with_copy = [sp]() {
//     std::cout << "Inside lambda_with_copy, captured sp use_count: "
//               << sp.use_count() << std::endl;
//     // do something with sp, for example, dereference it
//     std::cout << *sp << std::endl;
//   };
//   // lambda_with_copy();

//   // 创建一个函数对象func_with_copy，它存储了lambda_with_copy,
//   // 这里引用计数会增加1
//   std::function<void()> func_with_copy = lambda_with_copy;

//   // 调用函数对象，不改变引用计数
//   func_with_copy();

//   // 此时，sp的引用计数 3 ，因为func_with_copy仍持有lambda的拷贝
//   std::cout << "sp use_count after func_with_copy: " << sp.use_count()
//             << std::endl;

//   // Lambda表达式捕获sp的引用
//   // 在lambda里面使用引用，引用计数不会增加
//   auto lambda_with_reference = [&sp]() {
//     std::cout << "Inside lambda_with_reference, captured sp use_count: "
//               << sp.use_count() << std::endl;
//     // do something with sp, for example, dereference it
//     std::cout << *sp << std::endl;
//   };

//   // 创建一个函数对象func_with_reference，它存储了lambda_with_reference
//   std::function<void()> func_with_reference = lambda_with_reference;

//   // 调用函数对象，不改变引用计数
//   func_with_reference();

//   // 因为lambda_with_reference捕获的是引用，所以sp的引用计数仍然为1
//   std::cout << "sp use_count after func_with_reference: " << sp.use_count()
//             << std::endl;

//   return 0;
// }