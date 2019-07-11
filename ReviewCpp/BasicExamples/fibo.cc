#include <iostream>

int fibonacci(int n) {
  if (n <= 0)
    return 0;
  else if (n == 1)
    return 1;
  else
    return fibonacci(n - 2) + fibonacci(n - 1);
}

int main(void)
{
  for ( unsigned int i = 0; i < 10; ++i ) {
    std::cout << fibonacci(i) << ", ";
  }
  std::cout << std::endl;

  return 0;
}
