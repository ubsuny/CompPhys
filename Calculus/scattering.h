#ifndef scattering_h
#define scattering_h

#include "rootfinding.h"
#include "integrals.h"
#include "derivatives.h"
#include <vector>
#include <sstream>
#include <fstream>



/* 
   ------------------------------------------------
   lennard_jones : class to implement the Lennard-Jones potential. 
   Initialize with :
   * V0 : potential well depth

   Then execuate with operator()(r), which will return the Lennard-Jones
   potential at r. r must be in units of the potential's minimum, so
   the function is minimized at r = 1.0
   ------------------------------------------------  
*/
class lennard_jones  {
public : 
 lennard_jones( double V0, double r0=1. ) : _V0(V0), _r0(r0) {
  };
  double operator() ( double r) const { 
    return 4 * _V0 * (pow(r/_r0, -12.0) - pow(r/_r0, -6.0));
  }
  double V0() const { return _V0; }
  double r0() const { return _r0; }
protected : 
  double _V0;           /// Potential well
  double _r0; 
};

/* 
   ------------------------------------------------
   hard_sphere_potential : class to implement the hard-scattering ("billiard ball") potential. 
   Initialize with :
   * V0 : potential "inside" ball

   Then execuate with __call__(r), which will return V0 for r < 1.0, and 0 for r > 1.0.
   Here, r must be in units of the potential's width. 
   ------------------------------------------------  
*/
class hard_sphere_potential  {
public : 
 hard_sphere_potential( double V0, double r0=1.0 ) : _V0(V0), _r0(r0) {
  }
  double operator()( double r) const {
    if ( r < _r0 ) return _V0;
    else return 0.0;
  }
  double V0() const { return _V0; }
  double r0() const { return _r0; }
protected : 
  double _V0;
  double _r0; 
};


/* 
   ------------------------------------------------
   f_r_min:  
   class to implement the computation to find f(r_min), the
   distance at the point of closest approach (PCA).
   Note that r_min must be found numerically using a root-finding
   method of this function. 
     
   Returns the function 1 - (b/r)**2 - V(r)/E. 

   ------------------------------------------------  
*/
template< typename VFunctor >
class f_r_min  {
public : 

  f_r_min( VFunctor const & V, double E, double b ) : _V(V), _E(E),_b(b) {    
  }
  double operator()( double r ) const {
    double Vr = _V(r);
    return 1 - pow(_b / r, 2.0) - Vr / _E;
  }
protected : 
  VFunctor  _V;
  double    _E;
  double    _b;
};

/*
  ------------------------------------------------  
  dTheta_dr : 
  class to implement d(Theta) / d(r),
  the scattering amplitude of a particle scattering
  off of a potential V (r). Will utilize an instance of "f_r_min" to
  compute the distance at the point of closest approach (PCA).

  Returns : 1.0 / sqrt( abs(f_r_min(r)) ) / pow(r,2.0)

  ------------------------------------------------  
*/
template< typename VFunctor>
class dTheta_dr  {
public : 

  dTheta_dr( VFunctor const & V, double E, double b ) : _V(V), _E(E),_b(b), _frmin(V,E,b) {
  }
  double operator()(double r) const {
    double integrand = _frmin(r);
    integrand = 1 / sqrt(std::abs(integrand)) / pow(r, 2.0);
    return integrand;
  }
protected : 
  VFunctor _V;
  double   _E;
  double   _b;
  f_r_min<VFunctor>  _frmin;
};


/* 
   ------------------------------------------------
   CrossSection : class template to implement the full scattering amplitude of a particle of
   energy E and impact parameter b, scattering off a potential V. The distance r is 
   calculated in units of the fundamental parameter of the potential "VFunctor". 


   Initialize with :
   * VFunctor V   : Template parameter, represents a class that satisfies " double operator()( double x) const {} "
   * double E     : energy 
   * double b     : impact parameter
   * double r_max : maximum r to consider
   * uint   steps : maximum number of steps

   Compute the trajectory as : 
   std::vector< std::pair<double,double> > traj;
   double deflection = 0.0;
   calculate_trajectory( deflection, trajectory );

   Uses : 
   * f_r_min   : Functor to minimize to find r_min
   * dTheta_dr : Functor to integrate to find deflection. 
                 Calls f_r_min
   ------------------------------------------------  
*/
template< typename VFunctor>
class CrossSection  {
public : 
  typedef std::pair<double,double>           RThetaType;
  typedef std::vector< RThetaType >          Trajectory;



  CrossSection( VFunctor const & V, double E, double b, double r_max, unsigned int steps ) :
    _V(V), _E(E), _b(b), _r_max(r_max), _steps(steps), _frmin(V,E,b), _dThetaDr(V,E,b)
  {
  }

    Trajectory const & get_trajectory( ) const{ return _trajectory; }

  double calculate_trajectory()
  {    
    // set up initial conditions at projection point
    _trajectory.clear(); 
    double deflection = 0.;
    const double pi = 4 * atan(1.0);
    double d_theta = -asin(_b / _r_max);  // change from z = -infinty
    RThetaType r_theta;          // current position (r, theta)
    r_theta.first = _r_max;
    r_theta.second = pi + d_theta;
    _trajectory.clear();
    _trajectory.push_back(r_theta);
    deflection = pi - 2 * d_theta ;
    
    // find the distance of closest approach
    double dr = - _r_max / 100.0;      // step size for root finding
    double r_min = root_simple(_frmin, _r_max, dr);

    // integrate to find successive changes in theta
    dr = (_r_max - r_min) / _steps;   // step size for trajectory
    double accuracy = 1e-6;
    for (unsigned i = 0; i < _steps; i++) {
      double r_upper = r_theta.first;
      double r_lower = r_upper - dr;
      d_theta = - _b * adaptive_trapezoid<double>(_dThetaDr, r_lower, r_upper, accuracy);
      r_theta.first -= dr;
      r_theta.second += d_theta;
      _trajectory.push_back(r_theta);
      deflection += 2 * d_theta;
    }

    // use symmetry to get outgoing _trajectory points
    for (int i = _steps - 1; i > 0; i--) {
      r_theta.first += dr;
      d_theta = _trajectory[i].second - _trajectory[i-1].second;
      r_theta.second += d_theta;
      _trajectory.push_back(r_theta);
    }

    return deflection;
  }


protected :
  VFunctor            _V;          /// Template parameter representing potential function/functor
  double              _E;          /// Energy (units of V0 in _V)
  double              _b;          /// Impact parameter (units of r)
  double              _r_max;      /// Maximum r to consider
  unsigned int        _steps;      /// Maximum number of steps to consider
  f_r_min<VFunctor>   _frmin;      /// f(r_min) : function to minimize to find r_min
  dTheta_dr<VFunctor> _dThetaDr;   /// dTheta / dR : function to integrate to find deflection
  Trajectory          _trajectory; /// trajectory of r and theta
};

#endif 
