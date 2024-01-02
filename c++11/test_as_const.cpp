#include <cassert>
#include <string>
#include <type_traits>
#include <utility>

int main() {
  std::string mutableString = "Hello World!";
  auto&& constRef = std::as_const(mutableString);

  mutableString.clear();  // OK
  //   constRef.clear();       // Error: 'constRef' is 'const' qualified,
  //        but 'clear' is not marked const,您正在尝试调用一个非常量成员函数
  //        clear，但是该函数的调用对象是一个常量对象，因此产生了错误。

  assert(&constRef == &mutableString);
  assert(&std::as_const(mutableString) == &mutableString);

  using ExprType =
      std::remove_reference_t<decltype(std::as_const(mutableString))>;

  static_assert(std::is_same_v<std::remove_const_t<ExprType>, std::string>,
                "ExprType should be some kind of string.");
  static_assert(!std::is_same_v<ExprType, std::string>,
                "ExprType shouldn't be a mutable string.");
}