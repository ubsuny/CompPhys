#include "example.hpp"

// Define your function as you need.
int sum_int(std::vector<int> const & vec)
{
  int sum = 0;
  for ( auto i : vec ) {
    sum += i;
  }
  return sum;
}
