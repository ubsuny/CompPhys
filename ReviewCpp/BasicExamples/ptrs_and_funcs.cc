#include <iostream>

void increment1( int p){ ++p; std::cout << "p = " << p << std::endl;}
void increment2( int &p){ ++p; std::cout << "p = " << p << std::endl;}
void increment3( int *p){ ++(*p); std::cout << "*p = " << *p << std::endl;}


int main(void){

  int x = 3;
  int & rx = x;
  int * px = &x;
  std::cout << "0: x = " << x << std::endl;
  increment1(x);
  std::cout << "1: x = " << x << std::endl;
  increment2(rx);
  std::cout << "2: x = " << x << std::endl;
  increment3(px);
  std::cout << "3: x = " << x << std::endl;
  
  return 0;
}
