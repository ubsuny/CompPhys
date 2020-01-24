import matplotlib
matplotlib.rcParams['legend.fancybox'] = True
import matplotlib.pyplot as plt

import sys
import math
import numpy as np

class ODEState :
    def __init__(self,t,pos,vel) :
        self.t = t
        self.pos = pos
        self.vel = vel

    def __str__(self):
        s = ' ('
        for p in self.pos :
            s += '%6.2f ' % ( p )
        s += '),  ('
        for p in self.vel :
            s += '%6.2f ' % ( p )
        s += ')'
        return s

def read_orbit(filename, dim=3) :
    file = open( filename, 'r')
    lines = file.readlines()

    nobj = int(lines[0].rstrip())
    nSteps = len(lines) // ( nobj + 2 )
    iStepSize = nobj+2
    
    snapshots = []
    
    for iStep in range(nSteps):
        n = int( lines[iStep*iStepSize + 0] )
        t = float( lines[iStep*iStepSize + 1] )

        states = []
        for ival in range(2,iStepSize) :            
            vals = lines[iStep*iStepSize + ival].rstrip().split()
            odestate = ODEState( t, [float(k) for k in vals[1:dim+1]], [float(k) for k in vals[dim+1:2*(dim+1)] ] ) 
            
            states.append( odestate )
        snapshots.append(states)



    return nobj, snapshots




def plot_orbit(filename):

    n, snapshots = read_orbit( filename )

    x = np.zeros( (n, len(snapshots) ) )
    y = np.zeros( (n, len(snapshots) ) )

    for isnapshot,snapshot in enumerate(snapshots) :
        for iparticle, particle in enumerate(snapshot):
            x[iparticle][isnapshot] = particle.pos[0]
            y[iparticle][isnapshot] = particle.pos[1]
            
    colors = ['b','r','m']
    #print m
    for ival in range(3):
        plt.scatter( x[ival,:], y[ival,:], c=colors[ival])
    

    plt.show()
    

if __name__ == "__main__" :
    plot_orbit(sys.argv[1])
