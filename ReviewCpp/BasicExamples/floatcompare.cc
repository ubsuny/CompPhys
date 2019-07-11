#include <iostream>

int main(void) {

  float f1 = 5.0f;
  float f2 = 5.0000001f;

  if ( f1 == f2 ) {
    std::cout << "Nuke!" << std::endl;
  } else {
    std::cout << "Tweet!" << std::endl;
  }

  return 0;
}
