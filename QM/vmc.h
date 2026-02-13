// Variational Monte Carlo for the harmonic oscillator
#ifndef vmc_h
#define vmc_h

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <random>


class QHO {
public :

  QHO(int Nin, double alphain, int MCStepsin); 

  
  void zeroAccumulators();

  // Probability of the trial given the previous x
  double p(double xTrial, double x);

  // local energy
  double ELocal(double xi);

  // Perform one Metropolis step
  void MetropolisStep(); 

  // runs N Metropolis steps sequentially
  void oneMonteCarloStep(); 

  // Runs 20% of MCSteps to adjust
  // the step size so acceptance ~ 50%
  void adjustStep(); 

  // production steps
  void doProductionSteps( );

  void printout();

  void normPsi();

  std::vector<double> const & getPsiSquared() const { return psi_squared_; }

  double getEAvg() const { return E_sum_ / double(N_) / MC_steps_;}
  double getEVariance() const { double E_avg = getEAvg(); return E_squared_sum_ / double(N_) / MC_steps_ - E_avg * E_avg;}


  double getXMin() const { return x_min_;}
  double getXMax() const { return x_max_;}
  double getDx() const { return dx_; }
  
protected :

  // C++11 random number generator from Mersenne twister. 
  std::random_device rd_;
  std::mt19937 rng_;
  std::uniform_real_distribution<> uniform_;
  std::normal_distribution<> gaussian_;

  int N_;                         // number of walkers
  std::vector<double> x_;         // walker positions
  double delta_;                  // step size
  double E_sum_;                   // accumulator to find energy
  double E_squared_sum_;                // accumulator to find fluctuations in E
  double x_min_ = -10;             // minimum x for histogramming psi^2(x)
  double x_max_ = +10;             // maximum x for histogramming psi^2(x)
  double dx_ = 0.1;               // psi^2(x) histogram step size
  std::vector<double> psi_squared_;    // psi^2(x) histogram
  int n_psi_squared_;                   // size of array
  double alpha_;                  // trial function is exp(-alpha*x^2)
  int n_accept_;                   // accumulator for number of accepted steps
  int MC_steps_;                   // number of MC steps
};
  



#endif 
