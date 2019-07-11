#include <iostream>
int main(void){
  unsigned int i = 1000;
  for( unsigned int i = 0; i < 10; ++i ) {
    std::cout << i << std::endl;
  }
  std::cout << "Outside the loop, i = " << i << std::endl;
  return 0;
}
