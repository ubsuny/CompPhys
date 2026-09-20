#include "example.h"

int sum_int(std::vector<int> const & vec)
{
  int sum = 0;
  for ( auto i : vec ) {
    sum += i;
  }
  return sum;
}
