// Diffusion Monte Carlo program for the 3-D harmonic oscillator
#ifndef dmc_h
#define dmc_h

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <random>


class DiffusionMC {
public:
  
  DiffusionMC(int nt, double idt);

  // harmonic oscillator in DIM dimensions
  double V( std::vector<double> const & r);
  void ensureCapacity(int index);
  void zeroAccumulators() ;
  void oneMonteCarloStep(int n);
  void oneTimeStep();
  
  inline int getDIM() const { return DIM;}
  inline int getNPSI() const { return NPSI;}
  inline std::vector<double> const & getPsi() const { return psi;}
  inline double getESum() const { return ESum;}
  inline double getESqdSum() const { return ESqdSum;}
  inline double getRMax() const { return rMax; }


  void printout(std::ostream & out, int skip = -1 );
  
  void run( int timeSteps );

  
protected:
  // C++11 random number generator from Mersenne twister. 
  std::random_device rd;
  std::mt19937 gen;
  std::uniform_real_distribution<> dis;
  std::normal_distribution<> gausdev;
  
  static const int DIM = 3;      // dimensionality of space
  static const int NPSI = 100;   // number of bins for wave function

  // random walkers
  int N;                         // current number of walkers
  int N_T;                       // desired target number of walkers
  std::vector< std::vector<double> > r;   // x,y,z positions of walkers
  std::vector<bool> alive;                // is this walker alive?

  double dt;                              // Delta_t set by user
  double E_T;                             // target energy

  // observables
  double ESum;                            // accumulator for energy
  double ESqdSum;                         // accumulator for variance
  double rMax = 4;                        // max value of r to measure psi
  std::vector<double> psi;                // wave function histogram

};


#endif
