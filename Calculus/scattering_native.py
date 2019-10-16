from trapezoid import *
from math import *
from numpy import array
from root_finding import *

# Calculating the deflection angle by
# integrating the differential cross section
# of a scattering amplitude

######################################################################
#  Important note : All of the distances are in units of the
#                   distance parameter of the potential!
######################################################################

class lennard_jones :
    '''
    lennard_jones : class to implement the Lennard-Jones potential. 
    Initialize with :
        * V0 : potential well depth

    Then execuate with __call__(r), which will return the Lennard-Jones
    potential at r. r must be in units of the potential's minimum, so
    the function is minimized at r = 1.0
    '''
    V0 = 0.0
    def __init__( self, V0) :
        self.V0 = V0

    # Note : r is in units of r0 of L-J potential
    def __call__( self, r ) :
        if r < 0.0 :
            print 'Error! Value for r must be positive!'
            exit(1)
        return 4 *  self.V0 * ( pow( r, -12) - pow(r,-6))

class hard_sphere_potential :
    '''
    hard_sphere_potential : class to implement the hard-scattering ("billiard ball") potential. 
    Initialize with :
        * V0 : potential "inside" ball

    Then execuate with __call__(r), which will return V0 for r < 1.0, and 0 for r > 1.0.
    Here, r must be in units of the potential's width. 
    '''
    V0 = 0.0
    def __init__( self, V0 ) :
        self.V0 = V0
    
    def __call__( self, r ) :
        if r < 0.0 :
            print 'Error! Value for r must be positive!'
            exit(1)
        if r < 1.0 :
            return self.V0
        else :
            return 0


class Theta :
    '''
    Theta : class to implement the total scattering amplitude of a particle scattering
            off of a potential V(r). Will utilize dTheta_dr, and integrate it from
            r = -inf to inf. This is done by first finding the root of f_r_min.

            This expects that r is in units of the natural width of the potential.
            So, for a Lennard-Jones potential, r is in units of r0. For a hard scattering
            potential, it is in units of the width of the potential box. 

    Initialize with :
         * V     : potential to utilize (i.e. an instance of hard_sphere_potential, lennard_jones, etc)
                 : Must satisfy V(r)
         * E     : energy of incoming particle
         * b     : impact parameter of incoming particle
         * r_max : projection radius
         * steps : number of steps from r_min to r_max

    Then will compute the trajectory with "trajectory", which returns
    the total deflection ("deflection") along with the (r,theta)
    positions as a tuple of numpy "array" classes:
    [ array([r0,theta0]),
        array([r1,theta1]),
        array([r2,theta2]),
        ...
    ]

    To do this, utilizes :

    - f_r_min :
    implement the computation to find f(r_min), the
    distance at the point of closest approach (PCA).
    Note that r_min must be found numerically using a root-finding
    method of this function.

         Returns : 1 - (b/r)**2 - V(r)/E. 


    - dTheta_dr : 
    implement d(Theta) / d(r),
    the scattering amplitude of a particle scattering
    off of a potential V (r). Will utilize an instance of "f_r_min" to
    compute the distance at the point of closest approach (PCA).

         Returns : 1.0 / sqrt( abs(f_r_min(r)) ) / pow(r,2.0)

    
    '''
    V = None   # Must satisfy V.__call__(r)
    E = 0.0
    b = 0.0
    r_max = 0.0
    steps = 0
    dTdr = None
    def __init__( self, V, E, b, r_max, steps ) :
        self.V = V
        self.E = E
        self.b = b
        self.r_max = r_max
        self.steps = steps

    def f_r_min( self, r ) :
            return 1 - pow(self.b / r,2.0) - self.V(r) / self.E

    def dTheta_dr( self, r ) :
        X = self.f_r_min( r )
        return 1.0 / sqrt( abs(X) ) / pow(r,2.0)

    def trajectory( self ) :
        # Define theta step : 
        dtheta = -1.0 * asin( self.b / self.r_max )
        # To return : list of trajectories
        rtheta = [self.r_max, pi + dtheta]
        traj = [ array( rtheta ) ]
        # To return : Total deflection
        deflection = pi - 2*dtheta
        

        # Find the distance of closest approach with the "root_simple" method
        dr = -1.0 * self.r_max / 100
        r_max = self.r_max
        r_min = root_simple( self.f_r_min, r_max, dr)
        
        # Integrate to find successive changes in theta :
        dr = (r_max - r_min) / self.steps
        accuracy = 1e-6
        for i in xrange(self.steps) :
            r_upper = traj[i][0]
            r_lower = r_upper - dr
            itheta = traj[i][1]
            dtheta = -self.b * adaptive_trapezoid( self.dTheta_dr, r_lower, r_upper, accuracy )
            rtheta[0] -= dr
            rtheta[1] += dtheta
            traj.append( array( rtheta ) )
            deflection += 2 * dtheta


        # Use symmetry to get the outgoing trajectory points
        for i in range( self.steps-1, 0, -1) :
            rtheta[0] += dr
            dtheta = traj[i][1] - traj[i-1][1]
            rtheta[1] += dtheta
            traj.append( array( rtheta ) )

        return [deflection, traj]


def main() :
    print ' Classical scattering from Lennard-Jones potential'
    E = 0.705
    print ' E = ' + str(E)
    b_min = 0.6
    db = 0.3
    n_b = 6
    V = lennard_jones( V0 = 1.0 )
    for i in xrange(n_b) :
        b = b_min + db*i
        theta = Theta( V, E, b, 3.5, 100 )
        [deflection,trajs] = theta.trajectory()
        print ' {0:4.2f} : {1:6.2f}'.format( b, deflection )
        trajfile = open( 'trajfile_py_' + str(i) + '.data', 'w' )
        for traj in trajs :
            s = '{0:8.4f} {1:8.4f}\n'.format( traj[0] * cos( traj[1] ), traj[0] * sin(traj[1]) )
            trajfile.write( s )
        trajfile.close()

    print 'Finished! Trajectories are in trajfile[i].data'

if __name__ == "__main__" :
    main()
