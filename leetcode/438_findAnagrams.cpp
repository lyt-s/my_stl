#include <iostream>
#include <unordered_map>
#include <vector>

std::vector<int> findAnagrams(std::string s, std::string p) {
  std::vector<int> result;
  std::unordered_map<char, int> need, window;
  int left = 0, right = 0;
  int valid = 0;
  for (auto i : p) {
    need[i]++;
  }

  while (right < s.size()) {
    char c = s[right];
    right++;
    window[c]++;
    if (need.count(c)) {
      if (window[c] == need[c]) {
        valid++;
      }
    }

    while ((right - left) == p.size()) {
      if (valid == need.size()) {
        result.push_back(left);
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
  return result;
}

int main() {
  std::string s, p;
  std::cin >> s >> p;

  std::vector<int> outputs;

  outputs = findAnagrams(s, p);
  for (auto i : outputs) {
    std::cout << i << " ";
  }
  return 0;
}