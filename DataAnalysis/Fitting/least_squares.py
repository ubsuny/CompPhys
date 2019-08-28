import numpy as np

# define a function to linear fit x-y data without error bars
def least_squares(x, y):    
    """Perform a least-squares fit to data (x,y)

    Args :
       x : x values
       y : y values

    Returns :
       a : intercept
       b : slope
       sigma : total uncertainty (sqrt(variance/(n-2)))
       sigma_a : uncertainty on a
       sigma_b : uncertainty on b

    """

    n = len(x)   # number of galaxies

    if n <= 2 :
        print ('Error! Need at least two data points!')
        exit()

    # Compute all of the stat. variables we need
    s_x = np.sum(x)
    s_y = np.sum(y)
    s_xx = np.sum( x**2 )
    s_xy = np.sum( x*y )
    denom = n * s_xx - s_x**2
    if abs( denom ) < 0.000001 : 
        print ('Error! Denomominator is zero!')
        exit()

    # Compute y-intercept and slope 
    a = (s_xx * s_y - s_x * s_xy) / denom
    b = (n*s_xy - s_x * s_y) / denom   

    # Compute uncertainties
    if n > 2 : 
          sigma = np.sqrt(np.sum((y - (a+b*x))**2 ) / (n-2))
          sigma_a = np.sqrt(sigma**2 * s_xx / denom)
          sigma_b = np.sqrt(sigma**2 * n / denom)
    else :
          sigma = 0.
          sigma_a = 0.
          sigma_b = 0.

    return [a, b, sigma, sigma_a, sigma_b]    
