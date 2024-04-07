
#include <stack>
#include <string>
#include <utility>
std::string decodeString(const std::string s) {
  std::stack<std::pair<std::string, int>> st;

  std::string res = "";
  int mul = 0;

  for (auto c : s) {
    if (c == '[') {
      st.push({res, mul});
      int mul = 0;
      res = "";
    } else if (c == ']') {
      auto& [last_res, cur_mul] = st.top();
      st.pop();
      std::string temp = last_res;
      for (int i = 0; i < cur_mul; ++i) {
        temp += res;
      }
      res = temp;
    } else if ('0' <= c && c <= '9') {
      mul = mul * 10 + c - '0';
    } else {
      res += c;
    }
  }
  return res;
}

int main() {}