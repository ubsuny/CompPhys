import sys
import math
import numpy as np
import random

def generate_random_start(n=15,t=0,m=1):
    
    print (n)
    print (t)
    vals = np.random.uniform(-1,1, size=(n,4))
    
    
    for i in range(n):
        print (' %6d %+10.5e %+10.5e %+10.5e %+10.5e %+10.5e %+10.5e' % ( m, vals[i,0], vals[i,1], 0, vals[i,2], vals[i,3], 0) )


if __name__ == "__main__":
    generate_random_start()
