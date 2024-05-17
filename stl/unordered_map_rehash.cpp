#include <iostream>
#include <unordered_map>

///@brief 向 @c map 中添加 n 个int类型值

void insert_n(std::unordered_map<int, int>& map, int start, int n) {
  for (int idx = start; idx < start + n; ++idx) {
    map.insert({idx, idx});
  }

  std::cout << "bucket_cout: " << map.bucket_count()           // 桶的个数
            << "|size: " << map.size()                         // 元素个数
            << "|load_factor: " << map.load_factor() << '\n';  // 负载因子
}

int main(int argc, char* const argv[]) {
  std::unordered_map<int, int> map;
  insert_n(map, 0, 0);  // 初始化状态
  insert_n(map, 0, 1);
  insert_n(map, 1, 3);
  insert_n(map, 3, 4);
  insert_n(map, 7, 1);  // 满负载
  insert_n(map, 8, 1);  // Rehash
  insert_n(map, 9, 4);
  insert_n(map, 13, 1);

  return 0;
}

// // 输出如下：
// bucket_cout : 8 | size : 1 | load_factor : 0.125 bucket_cout : 8 | size : 4 |
//     load_factor : 0.5 bucket_cout : 8 | size : 7 |
//     load_factor : 0.875 bucket_cout : 8 | size : 8 |
//     load_factor : 1 bucket_cout : 64 | size : 9 | load_factor : 0.140625
