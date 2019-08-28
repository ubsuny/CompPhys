import math
import numpy as np
import matplotlib.pyplot as plt

from least_squares import least_squares


def main():
    # distances in Mpc
    r = np.array([ 0.032, 0.034, 0.214, 0.263, 0.275, 0.275, 0.45, 0.5,
          0.5,   0.63,  0.8,   0.9,   0.9,   0.9,   0.9,  1.0,
          1.1,   1.1,   1.4,   1.7,   2.0,   2.0,   2.0,  2.0 ])

    # velocities in km/s
    v = np.array([ +170, +290, -130, -70,  -185, -220, +200, +290,
          +270, +200, +300, -30,  +650, +150, +500, +920,
          +450, +500, +500, +960, +500, +850, +800, +1090 ])


    n = len(r)   # number of galaxies

    if n <= 2 :
        print ('Error! Need at least two data points!')
        exit()

    # Use our home-grown version
    [a, b, sigma, sigma_a, sigma_b] = least_squares(r,v)

    # Check against numpy's version:
    p,cov = np.polyfit( r, v, 1, cov=True)
    
    # Print out results
    print (' Least squares fit of', n, 'data points')
    print (' -----------------------------------')
    print (" Hubble's constant slope   b = {0:6.2f} +- {1:6.2f}  km/s/Mpc".format( b, sigma_b))
    print (" Intercept with r axis     a = {0:6.2f} +- {1:6.2f}  km/s".format( a, sigma_a))
    print (' Estimated v error bar sigma =', round(sigma, 1), 'km/s')
    print (" numpy's values:           b = {0:6.2f} +- {1:6.2f}  km/s/Mpc".format( p[0], np.sqrt(cov[0,0])))
    print ("                           a = {0:6.2f} +- {1:6.2f}  km/s/Mpc".format( p[1], np.sqrt(cov[1,1])))


    rvals = np.linspace(0., 2.0, 21)
    f = a + b * rvals
    fnp = p[1] + p[0] * rvals
    plt.figure(1)
    plt.scatter( r, v, label = "Data" )
    plt.plot( rvals, f , label="Our fit")
    plt.plot( rvals, fnp, label = "numpy fit")
    plt.xlabel("Distance (Mpc)")
    plt.ylabel("Velocity (km/s)")
    plt.legend()
    
    plt.show()


if __name__ == '__main__':
    main()
