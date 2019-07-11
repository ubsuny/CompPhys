#include <iostream>
int main(void){
  int i = 0;
  while( i < 5 ) {
    std::cout << i << ", ";
    ++i;
  }
  std::cout << std::endl;
  return 0;
}
