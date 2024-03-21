#include <iostream>
#include <memory>
using namespace std;

int main() {
  unique_ptr<int> q = make_unique<int>(2);
  // unique_ptr<int> q2(q.get());
  unique_ptr<int> q3(make_unique<int>(*q));

  std::unique_ptr<std::string> up1(
      std::make_unique<std::string>("Good morning"));

  // copy construct!
  std::unique_ptr<std::string> up2(std::make_unique<std::string>(*up1));
  cout << *up1 << endl;

  // safe copy construct!
  std::unique_ptr<std::string> up3(up1 ? std::make_unique<std::string>(*up1)
                                       : nullptr);
  // copy assignment!
  up2 = std::make_unique<std::string>(*up1);
  // safe copy assignment!
  up3 = up1 ? std::make_unique<std::string>(*up1) : nullptr;

  return 0;
}