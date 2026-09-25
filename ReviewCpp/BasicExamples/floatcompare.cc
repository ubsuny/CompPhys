#include <iostream>

int main(void) {

  float f1 = 5.0f;
  float f2 = 5.0000001f;

  if ( f1 == f2 ) {
    std::cout << "I’m sorry, Dave. I’m afraid I can’t do that." << std::endl;
  } else {
    std::cout << "No problem, come in Dave." << std::endl;
  }

  // Scan for breaking point
  for (int expt = -4; expt > -12; expt--) {
    float x = 1.;
    float y = 1. + std::pow(10., expt);
    std::cout << "x=" << x << ", y = 1. + " << std::pow(10., expt) << ", (x == y) = " << ((x == y) ? "true" : "false") << std::endl;
  }


  return 0;
}
