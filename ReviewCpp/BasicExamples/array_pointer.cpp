#include <iostream>
 
int main()
{
  double arr[5] = {0., 1., 2., 3., 4.};
  std::cout << "arr = " << arr << std::endl;
  std::cout << "*arr = " << *arr << std::endl;

  std::cout << "arr+1 = " << arr+1 << std::endl;
  std::cout << "*(arr+1) = " << *(arr+1) << std::endl;

  std::cout << "arr+2 = " << arr+2 << std::endl;
  std::cout << "*(arr+2) = " << *(arr+2) << std::endl;
  return 0;
}