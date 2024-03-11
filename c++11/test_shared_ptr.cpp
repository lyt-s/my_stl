#include <iostream>
#include <memory>

int main() {
  std::unique_ptr<std::string> up1(
      std::make_unique<std::string>("Good morning"));

  // copy construct!
  std::unique_ptr<std::string> up2(std::make_unique<std::string>(*up1));
  // safe copy construct!
  std::unique_ptr<std::string> up3(up1 ? std::make_unique<std::string>(*up1)
                                       : nullptr);
  // copy assignment!
  up2 = std::make_unique<std::string>(*up1);
  // safe copy assignment!
  up3 = up1 ? std::make_unique<std::string>(*up1) : nullptr;
  return 0;
}
