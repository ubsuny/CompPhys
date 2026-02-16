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
  void ensureCapacity(unsigned int index);
  void zeroAccumulators() ;
  void oneMonteCarloStep(int n);
  void oneTimeStep();
  
  inline int getDIM() const { return DIM;}
  inline int getNPSI() const { return NPSI;}
  inline std::vector<double> const & getPsi() const { return psi_;}
  inline double getESum() const { return E_sum_;}
  inline double getE2Sum() const { return E2_sum_;}
  inline double getRMax() const { return r_max_; }
  inline std::vector<double> const & getETHistory() const { return E_T_history_; }


  void printout(std::ostream & out, int skip = -1 );
  
  void run( int timeSteps );

  
protected:
  // C++11 random number generator from Mersenne twister. 
  std::random_device rd_;
  std::mt19937 rng_;
  std::uniform_real_distribution<> uniform_;
  std::normal_distribution<> gaussian_;
  
  static const int DIM = 3;      // dimensionality of space
  static const int NPSI = 100;   // number of bins for wave function

  // random walkers
  int N_;                         // current number of walkers
  int N_T_;                       // desired target number of walkers
  std::vector< std::vector<double> > r_walkers_;   // x,y,z positions of walkers
  std::vector<bool> alive_;                // is this walker alive?

  double dt_;                              // Delta_t set by user
  double E_T_;                             // target energy

  // observables
  double E_sum_;                            // accumulator for energy
  double E2_sum_;                         // accumulator for variance
  double r_max_ = 4;                        // max value of r to measure psi
  std::vector<double> psi_;                // wave function histogram
  std::vector<double> E_T_history_; // store all E_T values
  std::vector<std::vector<double>> psi_history_;

};


#endif
