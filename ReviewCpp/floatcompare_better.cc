#include <iostream>
#include <cmath>
#include <limits>

int main(void){
  float f1 = 5.0f;
  float f2 = 5.000000001f;
  float tolerance = 0.01f;

  if ( std::abs(f1 - f2) < tolerance) {
    std::cout << "Nuke!" << std::endl;
  } else {
    std::cout << "Tweet!" << std::endl;
  }


  if ( std::abs(f1 - f2) < std::numeric_limits<float>::epsilon() ) {
    std::cout << "Within machine precision!" << std::endl;
  }
}
