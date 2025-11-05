// This file basic.hpp provides functions for basic numerical algorithms
#ifndef derivatives_h
#define derivatives_h

#include <algorithm>
#include <cmath>
#include <complex>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>
#include <functional>

template< typename D, typename T = std::function<D(D)> >
D derivative_fivepoint( T const &f, D x, D h){
  /*
    f     : name of function to be differentiated
    x     : the point at which df/dx is required
    h     : step size
  */
    auto dfdx = ( f(x-2*h) - 8*f(x-h) + 8*f(x+h) - f(x+2*h)) / (12*h);
    return dfdx;
}

template< typename D, typename T = std::function<D(D)>>
D derivative_ridders(
    T const &f,            // name of function to be differentiated
    D x,                   // input: the point at which df/dx is required
    D h,                   // input: suggestion for an initial step size
    D& error)              // output: estimate of error by algorithm
{
    if (h == 0.0) {
        std::cerr << "derivative_ridders: h must be non-zero\n";
        exit(1);
    }
    const int n = 10;           // dimension of extrapolation table
    D a[n][n];             // extrapolation table
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            a[i][j] = 0;
    a[0][0] = (f(x + h) - f(x - h)) / (2 * h);
    D answer = 0;
    error = std::numeric_limits<T>::max();
    for (int i = 0; i < n; i++) {
        h /= 1.4;
        a[0][i] = (f(x + h) - f(x - h)) / (2 * h);
        D fac = 1.4 * 1.4;
        for (int j = 1; j <= i; j++) {
            a[j][i]=(a[j-1][i] * fac - a[j-1][i-1]) / (fac - 1);
            fac *= 1.4 * 1.4;
            D err = std::max(std::abs(a[j][i] - a[j-1][i]),
                             std::abs(a[j][i] - a[j-1][i-1]));
            if (err <= error) {
                error = err;
                answer = a[j][i];
            }
        }
        if (abs(a[i][i] - a[i-1][i-1]) >= 2 * error)
            break;
    }
    return answer;
}

#endif
