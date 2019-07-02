#include <iostream>

int main(void){

  int x = 10;
  int * px = &x;
  int & rx = x; 
  std::cout << "Value of px= " << px << ", dereferenced = " << *px << std::endl;
  std::cout << "Value of rx= " << rx << std::endl;
  *px = 7;
  std::cout << "x = " << x << std::endl;
  rx = 9;
  std::cout << "x = " << x << std::endl;
  return 0;
}
