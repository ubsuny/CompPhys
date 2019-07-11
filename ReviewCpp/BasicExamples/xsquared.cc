#include <iostream>

float xsquared( float x ){ return x*x; }

int main(void) {
  float x = 5.0;
  std::cout << xsquared(x) << std::endl;

  return 0;
}
