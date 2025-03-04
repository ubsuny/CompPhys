import numpy as np
import scipy.integrate
import scipy.optimize

class BVP :
    def __init__( self, fun, xbounds, ubounds, uprime, N ) :
        self.fun = fun             # function
        self.xbounds = xbounds     # boundaries
        self.ubounds = ubounds     # boundary values
        self.uprime = uprime       # guess for initial slope u'(0)
        self.N = N                 # step size
        self.xvals = None
        self.uvals = None
        self.uprimevals = None
        self.xplot = []
        self.uplot = []
        
class BVPShoot( BVP ) :
    step = None
    def __init__(self, fun, xbounds, ubounds, uprime) :
        BVP.__init__( self, fun, xbounds, ubounds, uprime, 0)
        
    def __call__( self, uprime ):
        self.uprime = uprime
        self.state = [ self.ubounds[0], self.uprime ]
        res = scipy.integrate.solve_ivp(fun=self.fun,t_span=self.xbounds,
                                y0=self.state, 
                                vectorized=False,
                                atol=1e-6,rtol=1e-4,
                                method='RK45')
        self.xvals = res.t
        self.uvals = res.y[0]
        self.uprimevals = res.y[1]
        self.state = [ self.uvals[-1], self.uprimevals[-1] ]
        self.xplot.append( np.array(self.xvals) )
        self.uplot.append( np.array(self.uvals) )
        return self.uvals[-1] - self.ubounds[1]
    
    def solve( self ) :
        res = scipy.optimize.root_scalar( self, bracket=[self.uprime-1, self.uprime+1] )
        #self.uvals
        return res


    
class BVPRelax( BVP ) :
    def __init__( self, fun, xbounds, ubounds, N) :
        BVP.__init__( self, fun, xbounds, ubounds, 0.0, N )
        self.xvals = np.linspace( xbounds[0], xbounds[1], N+1)
        self.uvals = np.zeros(N+1)
        self.uOld = np.zeros(N+1)
        self.dx = (xbounds[1]-xbounds[0])/(N+1)
        self.init()


    def init(self):        # linear interpolation between boundary conditions
        self.uvals = self.ubounds[0] + (self.xvals - self.xbounds[0]) / (self.xbounds[1] - self.xbounds[0]) * (self.ubounds[1] - self.ubounds[0])

    def relax(self):        # Jacobi algorithm
        self.uOld[:] = self.uvals[:]
        self.uvals[1:-1] = 0.5* ( self.uOld[2:] + self.uOld[:-2] - self.dx**2 * self.fun(self.uOld[1:-1]))
        self.xplot.append( np.array(self.xvals))
        self.uplot.append( np.array(self.uvals))

    def change(self):       # compute maximum change
        return np.max( np.abs(self.uvals - self.uOld) )