#ifndef Ising_h
#define Ising_h

#include <string>
#include <cmath>
#include <random>
#include <iostream>
#include <fstream>
#include <vector>


class Ising {
public :

  typedef std::vector<std::vector<double> > matrix_dtype;
  typedef std::vector<std::vector<int> > matrix_itype;

  Ising(double iJ=1.0, int iL=10, int iN_flips_per_step = 100, double iT=2.0, double iH=0.0);

  void resetAverages();
  
  void computeBoltzmannFactors();

  void thermalize(unsigned int n_therm);

  bool metropolisStep();

  void oneMCStepPerSpin();

  double magnetizationPerSpin();

  double energyPerSpin();

  void run(int n_mc_steps);

  double get_mAvg() const { return mAv_;}
  double get_m2Avg() const { return m2Av_;}
  double get_eAvg() const { return eAv_;}
  double get_e2Avg() const { return e2Av_;}

  std::vector<double> const & get_m_vals() const { return m_vals_; }
  std::vector<double> const & get_E_vals() const { return E_vals_; }

protected : 
  // C++11 random number generator from Mersenne twister. 
  std::random_device rd_;
  std::mt19937 rng_;
  std::uniform_real_distribution<> uniform_;
  

  double J_;                       // ferromagnetic coupling
  int L_, Lx_, Ly_;                // number of spins in x and y
  int N_spins_;
  int N_flips_per_step_;           // number of flips per recorded Metropolis-Hastings step
  matrix_itype spins_;                 // the spins
  double T_;                       // temperature
  double H_;                       // magnetic field
  bool thermalized_; // Did we run the thermalization yet?

  double w_[17][3];                // Boltzmann factors

  double acceptance_ratio_;
  int steps_;                      // steps so far

  double mAv_;
  double m2Av_;
  double eAv_;
  double e2Av_;

  std::vector<double> m_vals_, E_vals_; 
};



#endif
