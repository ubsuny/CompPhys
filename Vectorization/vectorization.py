#!/usr/bin/env python
import numpy as np
import time

def add_basic( a, b ):
    c = []
    for i in range(len(a)):
        c.append( a[i] + b[i] )
    return c

def main():
    N = 100000
    aA = np.random.rand(N)
    aB = np.random.rand(N)
    aC = np.zeros_like(aA)
    t1 = time.perf_counter()
    aC = np.add( aA, aB )
    t2 = time.perf_counter()       
    aD = add_basic(aA,aB)
    t3 = time.perf_counter()

    
    dt12 = t2 - t1 
    dt23 = t3 - t2
    
    print ( aC[0])
    print ( aD[0])
    print ( dt12 * 1e6 )
    print ( dt23 * 1e6 )
    return


if __name__ == "__main__":
    main()
