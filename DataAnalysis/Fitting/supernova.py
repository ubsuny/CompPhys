import math
import numpy as np
import matplotlib.pyplot as plt


def chi_square_fit(x, y, err):
    n = len(x)
    if n < 2 :
        print 'Error! Need at least 2 data points!'
        exit()
    S = sum(1/err**2)
    if abs(S) < 0.00001 :
        print 'Error! Denominator S is too small!'
        exit()
    S_x = sum(x/err**2)
    S_y = sum(y/err**2)
    t = (x - S_x/S) / err
    S_tt = sum(t**2)
    if abs(S_tt) < 0.00001 :
        print 'Error! Denominator S is too small!'
        exit()
    b = sum(t*y/err) / S_tt
    a = (S_y - S_x * b) / S
    sigma_a2 = (1 + S_x**2/S/S_tt) / S
    sigma_b2 = 1/S_tt
    if sigma_a2 < 0.0 or sigma_b2 < 0.0 :
        print 'Error! About to pass a negative to sqrt'
        exit()
    sigma_a = math.sqrt(sigma_a2)
    sigma_b = math.sqrt(sigma_b2)
    chi_square = sum(((y - a - b*x) / err)**2)
    return(a, b, sigma_a, sigma_b, chi_square)

print ' Chi-square fit of supernova data to a straight line'
print ' Reference: http://dark.dark-cosmology.dk/~tamarad/SN/'


data = np.genfromtxt(fname='Davis07_R07_WV07.dat', usecols=range(1,4),comments=';')
print(data)


logz_data = np.log10(data[:,0])
mu_data = data[:,1]
mu_err_data = data[:,2]

selection = mu_err_data < 0.0000001
if mu_err_data[ selection ].any():
    print 'Error! Uncertainties are too small!'
    exit()

plt.scatter( logz_data, mu_data )

fit = chi_square_fit(logz_data, mu_data, mu_err_data)
print ' slope =', fit[1], ' +- ', fit[3]
print ' intercept =', fit[0], '+-', fit[2]
if len(data) - 2 > 0 :
    print ' chi-square/d.o.f. = ', fit[4]/(len(data)-2)
else :
    print ' chi-square/d.o.f. undefined'

logz_data_vals = np.linspace(-2,0.5,10)
fitline = fit[0] + fit[1] * logz_data_vals
plt.plot(logz_data_vals,fitline)
plt.xlabel("logarithm of redshift")
plt.ylabel("distance modulus mu")
plt.show()
