#include <iostream>

int main(void) {

  int i = 0;
  std::cout << "Enter a number: ";
  std::cin >> i;



  if ( i > 2 ) {
    std::cout << "This is greater than 2. Way too much!" << std::endl;
  } else{
    if( i == 2 ) {
      std::cout << "Phew! This is 2." << std::endl;
    } else if (i == 1) {
      std::cout << "So close, but this is only 1!" << std::endl;
    } else {
      std::cout << "Yuck, this is even less than 1." << std::endl;
    }
  }

  return 0;
}
