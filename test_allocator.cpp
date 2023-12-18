#include <cstddef>
#include <cstdio>
#include <iostream>
#include <memory>
#include <vector>

struct MyStruct {
  int x;
  float y;
  MyStruct(int x, float y) : x(x), y(y) {
    std::cout << "MyStruct(int x, float y)" << std::endl;
  }
  ~MyStruct() {
    // 自定义析构函数
    std::cout << "MyStruct object is being destroyed.\n";
  }
};

int main() {
  std::vector<int> vec{1, 2, 3, 4, 5};
  std::allocator<int> alloc;
  auto print_list = [&](std::vector<int> const& vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
      printf("vec[%zd] = %d\n", i, vec[i]);
    }
  };

  auto print_pointer_list = [&](int* ptr) {
    while (ptr != nullptr && *ptr != 0) {
      printf("ptr = %d\n", *ptr);
      ++ptr;
    }
  };

  // 使用 allocator 分配未初始化内存
  int* p = alloc.allocate(vec.size());

  // 使用 uninitialized_copy 将 vec 中的元素复制到未初始化的内存中
  std::uninitialized_copy(vec.begin(), vec.end(), p);
  // for (int i = 0; i < vec.size(); ++i) {
  //   std::cout << p[i] << " ";
  // }
  print_pointer_list(p);
  std::cout << std::endl;

  // 使用完成后，需要手动调用 destructor 和 deallocate 释放资源
  for (std::size_t i = 0; i < vec.size(); ++i) {
    std::destroy_at(p + i);
  }
  alloc.deallocate(p, vec.size());

  //----uninitialized_copy_n---------------------------------------------------
  // 使用 allocator 分配未初始化内存
  int* p2 = alloc.allocate(vec.size());

  // 使用 uninitialized_copy_n 将 vec 中的前3个元素复制到未初始化的内存中
  std::uninitialized_copy_n(vec.begin(), 3, p2);
  // for (int i = 0; i < 3; ++i) {
  //   std::cout << p2[i] << " ";
  // }
  print_pointer_list(p2);
  std::cout << std::endl;
  // 使用完成后，需要手动调用 destructor 和 deallocate 释放资源
  for (std::size_t i = 0; i < 3; ++i) {
    std::destroy_at(p2 + i);
  }

  alloc.deallocate(p2, vec.size());

  //----uninitialized_fill-------------------------------------------------

  // 使用 allocator 分配未初始化内存
  int* p3 = alloc.allocate(5);

  // 使用 uninitialized_fill 将值42填充到未初始化的内存中
  std::uninitialized_fill(p3, p3 + 5, 42);
  // for (size_t i = 0; i < 5; ++i) {
  //   std::cout << p3[i] << " ";
  // }
  print_pointer_list(p3);
  // 使用完成后，需要手动调用 destructor 和 deallocate 释放资源
  for (std::size_t i = 0; i < 5; ++i) {
    std::destroy_at(p3 + i);
  }
  alloc.deallocate(p3, 5);

  //------------------------------------------------
  std::allocator<MyStruct> alloc_my_struct;

  // 使用 allocator 分配未初始化内存
  MyStruct* p_my_struct = alloc_my_struct.allocate(1);

  // 使用 construct_at 在未初始化的内存中构造一个 MyStruct 对象
  std::construct_at(p_my_struct, 42, 3.14f);

  // 使用完成后，需要手动调用 destroy_at 和 deallocate 释放资源
  std::destroy_at(p_my_struct);
  alloc.deallocate(p, 1);

  return 0;
}