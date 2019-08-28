%module our_fft
/* First: Include your own code.*/
%{
#define OUR_FFT
#include "our_fft.hpp"
%}
/* Next: declare the functions you want to use.*/
std::vector< std::complex<double> > our_fft(const std::vector< std::complex<double> >& data);
std::vector< std::complex<double> > our_dft(const std::vector< std::complex<double> >& data);

/* Finally: include any other libraries and types you need. 
Yes, you need one type per class, so that means one type per
template instance.*/


%include "std_vector.i"
%include "std_complex.i"

namespace std {
  %template(vector_complex_double) vector<std::complex<double> >;
};


