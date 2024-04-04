#include <algorithm>
#include <cstddef>
#include <iostream>
#include <unordered_map>

int noRepeatLongestSubstr(const std::string& str) {
  std::unordered_map<char, int> window;
  int left = 0, right = 0;
  int result = 0;
  while (right < str.length()) {
    char c = str[right];
    window[c]++;
    right++;

    while (window[c] > 1) {
      char d = str[left];
      left++;
      window[d]--;
    }
    result = std::max(right - left, result);
  }
  return result;
}

int main() {
  std::string str;
  std::cin >> str;

  std::cout << noRepeatLongestSubstr(str) << std::endl;
  return 0;
}