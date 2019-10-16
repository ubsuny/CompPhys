#include <vector>
#include <iostream>
#include <math.h>
#include "integrals.h"

using namespace std;


int main()
{
  unsigned n1=1,n2=0;
  cout << "Trapezoid quadrature of sin(x) [0, pi/2]" << endl;
  while ( n1 % 2 != 0 ) {
    cout << "Enter number of intervals desired for trapezoidal rule (must be even)" << endl;  
    cin >> n1;
  }
  double a = 0;
  double b = 2 * atan(1.0);
  double ans1 = trapezoid<double>(sin, a, b, n1);
  cout << "Trapezoidal rule : " << ans1 << endl;

  double ans2 = simpson<double>(sin, a, b, n1);
  cout << "Trapezoidal rule : " << ans2 << endl;

  double ans3 = adaptive_trapezoid<double>( sin, a, b, 0.0001);
  cout << "Adaptive trapezoidal rule : " << ans3 << endl;
}
