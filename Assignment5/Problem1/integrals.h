#ifndef integrals_h
#define integrals_h

#include <iostream>
#include <math.h>
#include <assert.h>
#include <functional>

//Approximates the definite integral of f from a to b by
//the composite trapezoidal rule, using n subintervals.
//From http://en.wikipedia.org/wiki/Trapezoidal_rule
template< typename D, typename T = std::function<D(D)> >
D trapezoid(            // performs trapezoid quadrature
    T const & f,        // function to be integrated
    D a,                // lower limit of integration
    D b,                // upper limit of integration
    unsigned n)         // number of subintervals
{
  assert ( n > 0 );
  D h = (b-a) / n;
  D s = f(a) + f(b);
  for ( unsigned i = 1; i < n; ++i ) {
    s += 2 * f(a + i*h);
  }
  return s * h / 2.0;
}

template< typename D, typename T = std::function<D(D)> >
D adaptive_trapezoid(   // performs iterative trapezoid quadrature
    T const &f,         // function to be integrated
    D a,                // lower limit of integration
    D b,                // upper limit of integration
    D acc,              // desired accuracy
    bool output=false)  // output on each iteration if output == true
{
    D old_sum = 1e30;
    D h = b - a;
    int n = 1;
    D sum = (f(a) + f(b)) / 2;
    if (output) {
        std::cout << "N = " << n+1 << ",  Integral = " << h*sum << std::endl;
	std::cout << "R = " << h * (old_sum - sum/2) << std::endl;
	std::cout << "acc = " << acc << std::endl;
    }
    while (fabs(h * (old_sum - sum/2)) > acc) {
        old_sum = sum;
        for (int i = 0; i < n; i++)
            sum += f(a + (i + 0.5) * h);
        n *= 2;
        h /= 2;
	if (output) {
	  std::cout << "N = " << n+1 << ",  Integral = " << h*sum << std::endl;
	  std::cout << "R = " << h * (old_sum - sum/2) << std::endl;
	  std::cout << "acc = " << acc << std::endl;
	}

    }
   return h * sum;
}



// Approximates the definite integral of f from a to b
// by the composite Simpson's rule, using n subintervals
template< typename D, typename T = std::function<D(D)> >
D simpson(              // performs iterative trapezoid quadrature
    T const & f,        // function to be integrated
    D a,                // lower limit of integration
    D b,                // upper limit of integration
    unsigned n)         // number of subintervals
{

  assert(n > 0);
  D h = (b-a) / n;
  D s = f(a) + f(b);

  for (unsigned i = 1; i < n; i += 2 ) {
    s += 4 * f(a + i * h);
  }
  for (unsigned i = 2; i < n-1; i += 2 ) {
    s += 2 * f(a + i * h);
  }
  return s * h / 3.0;

}

#endif
