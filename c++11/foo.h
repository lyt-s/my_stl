#pragma once
#include <cstdint>

inline int32_t i = 0;

// static 和 inline 的区别  todo  总结
// static int twice(int x) { return x * 2; };
// 这里和内联优化没有任何关系
inline int twice(int x) { return x * 2; };
void foo();