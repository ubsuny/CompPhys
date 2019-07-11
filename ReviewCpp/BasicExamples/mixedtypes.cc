#include <iostream>
int main(void) {
  float f = 1.999999;
  int i = f;
  std::cout << i << std::endl;
  float g = 2.0;
  std::cout << i / g << std::endl;
  std::cout << g / i << std::endl;
  return 0;
}
