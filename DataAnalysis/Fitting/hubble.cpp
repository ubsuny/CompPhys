#include <cmath>
#include <iostream>
using namespace std;


#include "least_squares.hpp"


int main() {

  const int n = 24;   // number of galaxies in Table 1

  std::vector<double> r = {     // distances in Mpc
    0.032, 0.034, 0.214, 0.263, 0.275, 0.275, 0.45, 0.5, 0.5, 0.63, 0.8, 0.9,
    0.9,   0.9,   0.9,   1.0,   1.1,   1.1,   1.4,  1.7, 2.0, 2.0,  2.0, 2.0
  };

  std::vector<double> v = {     // velocities in km/s
    +170, +290, -130, -70,  -185, -220, +200, +290, +270, +200, +300, -30,
    +650, +150, +500, +920, +450, +500, +500, +960, +500, +850, +800, +1090
  };

 
  if ( n < 2 ) {
    cout << "Error! Need at least two data points!" << endl;
    return 0;
  }

  // fit data to straight line
  double a, b, sigma, sigma_a, sigma_b;
  least_squares(r, v, a, b, sigma, sigma_a, sigma_b);

  // print results
  cout.precision(4);
  cout << " Least-squares fit of " << n << " data points\n"
       << " -----------------------------------\n"
       << " Hubble's constant slope   b  =  " << b
       << " +- " << sigma_b << " km/s/Mpc\n"
       << " Intercept with r axis     a  =  " << a
       << " +- " << sigma_a << " km/s\n"
       << " Estimated v error bar sigma  =  " << sigma << " km/s" << endl;
}
