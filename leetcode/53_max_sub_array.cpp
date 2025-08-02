#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
int maxSubArray(std::vector<int>& nums) {
  int result = nums[0];
  for (int i = 1; i < nums.size(); ++i) {
    if (nums[i - 1] > 0) {
      nums[i] += nums[i - 1];
    }
    result = std::max(result, nums[i]);
  }
  return result;
}

int main() {
  // int n;
  // std::cin >> n;
  // std::vector<int> nums(n, 0);
  // for (int i = 0; i < n; i++) {
  //   std::cin >> nums[i];
  // }

  std::string input;
  std::getline(std::cin, input);
  std::vector<int> numbers;
  std::stringstream ss(input);

  int number;
  char ch;
  while (ss >> ch) {  // 读取每个字符
    if (ch == ',' || ch == '[' || ch == ']') {
      continue;  // 跳过逗号和方括号
    } else {
      ss.unget();  // 将字符放回流中，因为这个字符可能是数字的一部分
      if (ss >> number) {           // 如果能从流中读出一个整数
        numbers.push_back(number);  // 将整数添加到向量中
      }
    }
  }

  // 输出所有读取的数字进行检查
  for (int num : numbers) {
    std::cout << num << " ";
  }
  std::cout << maxSubArray(numbers);
  // -2 1 -3 4 -1 2 1 -5 4
}