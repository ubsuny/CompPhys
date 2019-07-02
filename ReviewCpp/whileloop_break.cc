#include <iostream>
int main(void){
  int i = 0;
  std::cout << "Enter a number, negative number to quit" << std::endl;
  while( std::cin >> i ) {
    if ( i < 0 ) {
      std::cout << "Negative number entered, exiting." << std::endl;
      break;
    } else {
      std::cout << "You entered i=" << i << std::endl;
    }
  }
  return 0;
}
