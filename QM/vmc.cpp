// Variational Monte Carlo for the harmonic oscillator
#include "vmc.h"

QHO::QHO(int N_in, double alpha_in, int MC_steps_in) :
  rd_(), rng_(rd_()), uniform_(0,1.), gaussian_(),
  N_(N_in), alpha_(alpha_in), MC_steps_(MC_steps_in)
{
  x_.resize(N_); // create N_ walkers
  for (int i = 0; i < N_; i++) {
    x_[i] = uniform_(rng_)-0.5; // random initial positions in [-0.5, 0.5]
  }
  delta_ = 1;

  n_psi_squared_ = int((x_max_ - x_min_) / dx_);
  psi_squared_.resize(n_psi_squared_);
  n_accept_ = 0;

  zeroAccumulators();
}

void QHO::zeroAccumulators() {
  E_sum_ = 0;
  E_squared_sum_ = 0;
  for (int i = 0; i < n_psi_squared_; i++) {
    psi_squared_[i] = 0;
  }
}

double QHO::p(double x_trial, double x) {

  // compute the ratio of rho(xTrial) / rho(x)
  return exp(-2.0 * alpha_ * (x_trial*x_trial - x*x));
}

double QHO::ELocal(double xi) {

  // compute the local energy
  return alpha_ + xi * xi * (0.5 - 2 * alpha_ * alpha_);
}

void QHO::MetropolisStep() {

  // choose a walker at random
  int walker_n = int(uniform_(rng_) * N_);

  // make a trial move
  double x_trial = x_[walker_n] + delta_ * gaussian_(rng_);

  // Metropolis test
  if (p(x_trial, x_[walker_n]) > uniform_(rng_) ) {
    x_[walker_n] = x_trial;
    ++n_accept_;
  }

  // accumulate energy and wave function
  double e = ELocal(x_[walker_n]);
  E_sum_ += e;
  E_squared_sum_ += e * e;
  int i = int((x_[walker_n] - x_min_) / dx_);
  if (i >= 0 && i < n_psi_squared_)
    psi_squared_[i] += 1;
}

void QHO::oneMonteCarloStep() {

  // perform N Metropolis steps
  for (int i = 0; i < N_; i++) {
    MetropolisStep();
  }
}

void QHO::adjustStep() {
  // perform 20% of MCSteps as thermalization steps
  // and adjust step size so acceptance ratio ~50%
  int therm_steps = int(0.2 * MC_steps_);
  int adjust_interval = int(0.1 * therm_steps) + 1;

  std::cout << " Performing " << therm_steps << " thermalization steps ..."
	    << std::flush;
  for (int i = 0; i < therm_steps; i++) {
    oneMonteCarloStep();
    if ((i+1) % adjust_interval == 0) {
      delta_ *= n_accept_ / (0.5 * N_ * adjust_interval) ;
      n_accept_ = 0;
    }
  }
  std::cout << "\n Adjusted Gaussian step size = " << delta_ << std::endl;    
}


// production steps
void QHO::doProductionSteps( ) {
  zeroAccumulators();
  n_accept_ = 0;
  std::cout << " Performing " << MC_steps_ << " production steps ..." << std::flush;
  for (int i = 0; i < MC_steps_; i++)
    oneMonteCarloStep();
}

void QHO::printout() {

  // compute and print energy
  double E_avg = getEAvg(); 
  double E_variance = getEVariance(); 
  double error = sqrt(E_variance) / sqrt(double(N_) * MC_steps_);
  std::cout << "\n <Energy> = " << E_avg << " +/- " << error
	    << "\n Variance = " << E_variance << std::endl;

}


void QHO::normPsi() {
  double psi_norm = 0;
  for (int i = 0; i < n_psi_squared_; i++)
    psi_norm += psi_squared_[i] * dx_;
  for (int i = 0; i < n_psi_squared_; i++) {
     psi_squared_[i] /= psi_norm;
  }
}
