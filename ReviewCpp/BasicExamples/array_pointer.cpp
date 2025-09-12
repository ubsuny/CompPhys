#include <iostream>
 
int main()
{
  int arr[5] = {0, 1, 2, 3, 4};
  std::cout << "arr = " << arr << std::endl;
  std::cout << "*arr = " << *arr << std::endl;
  std::cout << "arr+1 = " << arr+1 << std::endl;
  std::cout << "*(arr+1) = " << *(arr+1) << std::endl;
  return 0;
}