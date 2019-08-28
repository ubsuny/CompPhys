from cmath import exp, pi
from math import sin, cos
import numpy as np

def discrete_transform(data):
    """Return Discrete Fourier Transform (DFT) of a complex data vector"""
    N = len(data)
    transform = np.zeros(N)
    for k in range(N):
        for j in range(N):
            angle = 2 * pi * k * j / N
            transform[k] += data[j] * exp(1j * angle)
    return transform

def fft(x):
    N = len(x)
    if N <= 1: return x
    elif N % 2 == 1:         # N is odd, lemma does not apply
        print ('N is ' + str(N) + ', fall back to discrete transform')
        return discrete_transform(x)
    even = fft(x[0::2])
    odd =  fft(x[1::2])
    return np.array( [even[k] + exp(-2j*pi*k/N)*odd[k] for k in range(N//2)] + \
                     [even[k] - exp(-2j*pi*k/N)*odd[k] for k in range(N//2)] )



def fft_power(x) :
    N = len(x)
    if N <=1 : return x
    power = np.zeros(N//2+1)
    power[0] = abs(x[0])**2
    power[1:N//2] = abs(x[1:N//2])**2 + abs(x[N-1:N//2:-1])**2
    power[N//2] = abs(x[N//2])**2
    power = power/N
    return power


def ifft(x) :
    from numpy import conj, divide

    # conjugate the complex numbers
    x = np.conj(x)
 
    # forward fft
    X = fft( x );
 
    # conjugate the complex numbers again
    X = np.conj(X)
 
    # scale the numbers
    X = X / len(X)

    return X
    
