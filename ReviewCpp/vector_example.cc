#include <iostream>
#include <vector>
 
int main()
{
  // Create a vector containing integers
  std::vector<int> v = {7, 5, 16, 8};
 
  // Add two more integers to vector
  v.push_back(25);
  v.push_back(13);
 
  // Iterate and print values of vector
  for(int n : v) {
    std::cout << n << std::endl;
  }

  // Another way to do that:
  for( std::vector<int>::const_iterator i = v.begin(); i != v.end(); ++i ) {
    std::cout << *i << std::endl;
  }
}
