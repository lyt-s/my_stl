#include <iostream>
#include <unordered_map>

int lengthOfLongestSubstring(std::string s) {
  std::unordered_map<char, int> need, window;
  int right = 0, left = 0;
  int result = 0;
  while (right < s.size()) {
    char c = s[right];
    window[c]++;
    right++;

    while (window[c] > 1) {
      char d = s[left];
      left++;
      window[d]--;
    }
    result = std::max(right - left, result);
  }
  return result;
}

int main() {
  std::string s;
  std::cin >> s;

  int result = lengthOfLongestSubstring(s);
  std::cout << result << std::endl;
  return 0;
}