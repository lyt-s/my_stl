
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

std::vector<std::vector<std::string>> groupStr(std::vector<std::string>& strs) {
  std::unordered_map<std::string, std::vector<std::string>> hash;

  std::vector<std::vector<std::string>> result;
  for (auto str : strs) {
    std::string key = str;
    std::sort(key.begin(), key.end());
    hash[key].push_back(str);
  }

  for (auto i : hash) {
    result.push_back(i.second);
  }

  return result;
}

int main() {
  std::string line;
  std::vector<std::string> words;

  std::getline(std::cin, line);

  std::stringstream ss(line);

  std::string word;
  char ch;
  while (ss >> ch) {
    if (ch == '[' || ch == ']') {
      continue;
    }
    if (ch == ',') {
      if (!word.empty()) {
        words.push_back(word);
        word.clear();
      }
    } else {
      word.push_back(ch);
    }
  }

  if (!word.empty()) {
    words.push_back(word);
  }

  // // 现在 vector 中包含了所有的单词
  // for (const std::string& w : words) {
  //   std::cout << w << std::endl;
  // }
  std::vector<std::vector<std::string>> result = groupStr(words);

  for (auto i : result) {
    std::cout << "[";
    for (unsigned long j = 0; j < i.size(); j++) {
      std::cout << i[j];
      if (j != i.size() - 1) {
        std::cout << ", ";
      }
    }
    std::cout << ']' << std::endl;
  }

  return 0;
}