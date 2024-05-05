#include <iostream>
#include <string>
#include <vector>

static int n = 0;

int main() {
  std::vector<char> characters;

  auto print_list = [&]() {
    for (char c : characters) std::cout << c << ' ';
    std::cout << '\n';
  };

  characters.assign(5, 'a');
  print_list();

  const std::string extra(6, 'b');
  characters.assign(extra.begin(), extra.end());
  print_list();

  characters.assign({'C', '+', '+', '1', '1'});
  print_list();

  int *a;
  a[0] = 1;
  a[1] = 2;
  a[2] = 3;
  std::cout << a[0] << '\n';
  std::cout << *a << '\n';
  std::cout << a[1] << '\n';
  std::cout << *(a + 1) << '\n';

  return 0;
}