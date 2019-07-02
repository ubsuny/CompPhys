#include <iostream>
#include <string>

int main(void) {

  std::string s1;
  std::cout << "Enter a string: ";
  std::cin >> s1;

  std::cout << "Your string is: " << s1 << std::endl;

  if (s1 == "Yay!") {
    std::cout << "Yay? Just what I was thinking!" << std::endl;
  }
}
