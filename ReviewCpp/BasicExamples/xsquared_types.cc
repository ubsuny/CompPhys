#include <iostream>

int squared(int x){ return x*x;}
float squared(float x){ return x*x;}
double squared(double x){ return x*x;}
long squared( long x) { return x*x;}

int main(void)
{
  int i = 5;
  long j = 10;
  float x = 0.5;
  double y = 1.5;

  std::cout << squared(i) << std::endl;
  std::cout << squared(j) << std::endl;
  std::cout << squared(x) << std::endl;
  std::cout << squared(y) << std::endl;

  return 0;
}
