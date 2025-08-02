#include <iostream>
#include <string>
#include <vector>

using namespace std;

string sub_str(string& str) {
  string result;
  vector<string> strs;
  int i = 0;
  for (i = 0; i < str.size(); i++) {
    if (str[i] == 'a' && str[i + 1] == 'b') {
      for (int j = i + 2; j < str.size() - 1; j++) {
        if (str[j] == 'a' && str[j + 1] == 'b') {
          strs.push_back(str.substr(i, j - i + 2));
          i = j + 2;
          break;
        }
      }
    }
  }

  for (auto s : strs) {
    cout << s << endl;
    if (s.size() > result.size()) {
      result = s;
    }
  }

  return result;
}

int main() {
  string str = "abc34$abywzs6openxeabccabac";
  cout << sub_str(str) << "\n";
  return 0;
}