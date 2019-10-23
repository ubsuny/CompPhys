import numpy as np


def polyfit(x, y, sigma, M):
    ''' 
        Description: Fit a polynomial of degree M. 
        
        Inputs:
            x = independent variable
            y = dependent variable
            sigma = uncertainties on y

        Internally defines :
            N = number of data points
            b = y / sigma
            A = design matrix

        Returns:
            a_fit = fitted coefficients
            sig_a = uncertainties on a_fit
            yy = fitted y values
            chi2 = chi squared for fit
        
    '''
    N = len(x)
    X = x.reshape( (len(x),1) )
    Y = y.reshape( (len(y),1) )
    S = sigma.reshape( (len(sigma),1) )
    i = np.linspace( 0,M,M+1 )
    A = np.power(X,i) / S
    Cinv = np.matmul(A.T,A)
    C = np.linalg.inv(Cinv)
    b = Y/S
    a = np.matmul(C,A.T)
    a = np.matmul(a,b).reshape(M+1)
    siga = np.sqrt( np.diagonal( C ) )
    yfit = np.polynomial.polynomial.polyval(x, a)
    chi2 = np.sum( ((y - yfit)/sigma)**2 )
    return a, siga, C, chi2, yfit
    
