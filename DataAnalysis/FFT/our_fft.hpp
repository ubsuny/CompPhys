#ifndef OUR_FFT_HPP
#define OUR_FFT_HPP
#include <complex>
#include <vector>


// Return Fast Fourier Transform (FFT) using Danielson-Lanczos Lemma
std::vector< std::complex<double> > our_fft(const std::vector< std::complex<double> >& data);
// Return discrete Fourier Transform (DFT)
std::vector< std::complex<double> > our_dft(const std::vector< std::complex<double> >& data);

#endif
