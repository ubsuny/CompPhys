// Path Integral Monte Carlo program for the 1-D harmonic oscillator
#ifndef pimc_h
#define pimc_h

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <random>


class PathIntegralMC{
public:

  PathIntegralMC(double itau, int iM, int inbins, double ixmax, double idelta, int iMC_steps); 

  // potential energy function
  double V(double x);

  // derivative dV(x)/dx used in virial theorem
  double dVdx(double x);

  int thermalize();

  void do_steps();
    

  bool Metropolis_step_accepted();

  std::vector<double> const & get_P() const {return P;}

  double get_x_min() const { return x_min; }
  double get_x_max() const { return x_max; }
  double get_dx() const { return dx; }
  double get_E_ave() const { return E_ave; }
  double get_E_var() const { return E_var; }
  
protected :

  // C++11 random number generator from Mersenne twister. 
  std::random_device rd;
  std::mt19937 gen;
  std::uniform_real_distribution<> dis;
  std::normal_distribution<> gausdev;
  
  double tau;                 // imaginary time period
  int M;                      // number of time slices
  double Delta_tau;           // imaginary time step
  std::vector<double> x;      // displacements from equilibrium of M "atoms"

  int n_bins;                 // number of bins for psi histogram
  double x_min;               // bottom of first bin
  double x_max;               // top of last bin
  double x_new;               // New x value after Metropolis step
  double dx;                  // bin width
  std::vector<double> P;      // histogram for |psi|^2

  double delta;               // Metropolis step size in x
  int MC_steps;               // number of Monte Carlo steps in simulation


  double E_ave;               // average energy
  double E_var;               // energy variance
};



#endif 
