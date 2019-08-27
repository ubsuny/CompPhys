
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "our_fft.hpp"

using namespace std;

// Return Discrete Fourier Transform (DFT) of a complex data vector
vector< complex<double> >
our_dft(const vector< complex<double> >& data)
{
    int N = data.size();
    vector< complex<double> > transform(N, 0.0);
    const double pi = 4 * atan(1.0);
    const complex<double> i(0.0, 1.0);
    for (int k = 0; k < N; k++)
        for (int j = 0; j < N; j++) {
            double angle = 2 * pi * k * j / double(N);
            transform[k] += data[j] * exp(i * angle);
        }
    return transform;
}

// Return Fast Fourier Transform (FFT) using Danielson-Lanczos Lemma
vector< complex<double> >
our_fft(const vector< complex<double> >& data)
{
    int N = data.size();
    if (N == 1)             // transform is trivial
        return data;
    else if (N % 2 == 1)    // transform is odd, lemma does not apply
        return our_dft(data);

    // perform even-odd decomposition and transform recursively
    vector< complex<double> > even(N / 2, 0.0);
    for (int j = 0; j < N / 2; j++)
        even[j] = data[2 * j];
    even = our_fft(even);
    vector< complex<double> > odd(N / 2, 0.0);
    for (int j = 0; j < N / 2; j++)
        odd[j] = data[2 * j + 1];
    odd = our_fft(odd);
    const double pi = 4 * atan(1.0);
    const complex<double> i(0.0, 1.0);
    complex<double> W = exp(2.0 * i * pi / double(N));
    complex<double> Wk = 1.0;
    vector< complex<double> > transform(N, 0.0);
    for (int k = 0; k < N; k++) {
        transform[k] = even[k % (N / 2)] + Wk * odd[k % (N / 2)];
        Wk *= W;
    }
    return transform;
}
