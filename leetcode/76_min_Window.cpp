

#include <algorithm>
#include <climits>
#include <iostream>
#include <string>
#include <unordered_map>
std::string minWindow(std::string s, std::string t) {
  std::unordered_map<char, int> need, window;
  int valid = 0;
  int left = 0, right = 0;
  int start = 0;
  int length = INT_MAX;
  for (auto i : t) {
    need[i]++;
  }
  while (right < s.length()) {
    char c = s[right];
    right++;
    window[c]++;

    if (need.count(c)) {
      if (window[c] == need[c]) {
        valid++;
      }
    }

    while (valid == need.size()) {
      if ((right - left) < length) {
        length = right - left;
        start = left;
      }
      char d = s[left];
      left++;
      if (need.count(d)) {
        if (window[d] == need[d]) {
          valid--;
        }
      }
      window[d]--;
    }
  }

  return length == INT_MAX ? "" : s.substr(start, length);
}

int main() {
  std::string s, t;

  std::cin >> s >> t;

  std::cout << minWindow(s, t);
  return 0;
  // ADOBECODEBANC ABC
}