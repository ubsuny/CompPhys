#include <iostream>

int main(void) {

  float f1 = 5.0f;
  float f2 = 5.0000001f;

  if ( f1 == f2 ) {
    std::cout << "I’m sorry, Dave. I’m afraid I can’t do that." << std::endl;
  } else {
    std::cout << "No problem, come in Dave." << std::endl;
  }

  return 0;
}
