import numpy as np

def derivative_fivepoint( f, x, h) :
    ''' f     : name of function to be differentiated
        x     : the point at which df/dx is required
        h     : step size
    '''
    dfdx = ( f(x-2*h) - 8*f(x-h) + 8*f(x+h) - f(x+2*h)) / (12*h)
    return dfdx
    
    
    
def derivative_ridders(f,x,h,n=10,verbose=False):
    ''' Purpose : to compute the derivative of f using Ridder's method.
        Algorithm : Uses polynomial extrapolation to compute the derivative.
                    Stores the "Neville's algorithm" tableaux in a table.
                    Initially compute symmetric difference differential and error
                    At each successive increase of the polynomial extrapolation,
                         reduce the step size
                         recompute the symmetric difference differential and error
                         if error is better, keep
                         else, continue
        
        f     : name of function to be differentiated
        x     : the point at which df/dx is required
        h     : suggestion for an initial step size
        n     : dimension of extrapolation table
        error : estimate of error by algorithm
    '''

    if h == 0.0 :
        print ("diff_Ridders: h must be non-zero")
        exit
    a = np.zeros( (n,n))             # extrapolation table

    a[0][0] = (f(x + h) - f(x - h)) / (2 * h)
    answer = 0.0
    error = np.nan_to_num( np.inf ) / 2.0  # get a large value for the error
    for i in np.arange(n) :
        if verbose:
            print("------------ i = ", i )
            print(a)
        h /= 1.4
        a[0][i] = (f(x + h) - f(x - h)) / (2 * h)
        fac = 1.4 * 1.4
        for j in np.arange(1,i+1) :
            a[j][i]=(a[j-1][i] * fac - a[j-1][i-1]) / (fac - 1)
            fac *= 1.4 * 1.4
            err = max(np.abs(a[j][i] - a[j-1][i]),
                      np.abs(a[j][i] - a[j-1][i-1]))
            if err <= error :
                error = err
                answer = a[j][i]

        if np.abs(a[i][i] - a[i-1][i-1]) >= 2 * error :
            break
    return answer,error
