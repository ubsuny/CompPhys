#include <iostream>
int main(void){

  for ( unsigned int i = 0; i < 10; ++i) {
    for ( unsigned int j = i; j < 10; ++j ){
      std::cout << "(" << j << ", " << i << "), ";
    }
    std::cout << std::endl;
  }
  return 0;
}
