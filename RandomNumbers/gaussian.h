#ifndef gaussian_h
#define gaussian_h

#include <cmath>

template<typename T>
class gaussian{
 public:
  
 gaussian( std::vector<T> const & iA, std::vector<T> const & isigma, std::vector<T> const & icenter ):
  A(iA), sigma(isigma), center(icenter)
  {
  }
  

 gaussian( gaussian const & g ):
  A(g.A), sigma(g.sigma), center(g.center)
  {
  }

 
  T operator() (T x)                 // probability distribution
  {
    T p = 0;
    for (unsigned int i = 0; i < A.size(); i++)
      p += A[i]*std::exp(-(x-center[i])*(x-center[i])/(2*sigma[i]*sigma[i]));
    return p;
  }

protected :
  
  std::vector<T>
    A,              // amplitudes
    sigma,          // widths
    center;         // positions of centers

};



#endif
