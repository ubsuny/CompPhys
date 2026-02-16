// Diffusion Monte Carlo program for the 3-D harmonic oscillator
#include "dmc.h"

DiffusionMC::DiffusionMC(int nt, double idt) :
  rd_(), rng_(rd_()), uniform_(0,1.), gaussian_(),
  N_T_(nt), dt_(idt)
{
  std::cout << "Hello from DiffusionMC" << std::endl;
  N_ = N_T_;                   // set N to target number specified by user
  ensureCapacity(N_);    
  for (int n = 0; n < N_; n++) {      
    for (int d = 0; d < DIM; d++)
      r_walkers_[n][d] = uniform_(rng_)- 0.5;
    alive_[n] = true;
  }
  zeroAccumulators();
  E_T_ = 0;                   // initial guess for the ground state energy

}



double DiffusionMC::V(std::vector<double> const & r) {          // harmonic oscillator in DIM dimensions
  double r2 = 0;
  for (int d = 0; d < DIM; d++) {
    r2 += r[d] * r[d];
  }
  return 0.5 * r2;
}

void DiffusionMC::ensureCapacity(unsigned int index) {

  if (index < r_walkers_.size()) {         // no need to expand array
    return;                // do nothing
  } else {
    r_walkers_.resize(2 * index, std::vector<double>(DIM));      
    alive_.resize(2 * index, false);      
    return;
  }
}
  
void DiffusionMC::zeroAccumulators() {
  E_sum_ = 0;
  E2_sum_ = 0;
  psi_.clear();
  psi_.resize(NPSI);
}


void DiffusionMC::oneMonteCarloStep(int n) {

  // Diffusive step
  for (int d = 0; d < DIM; d++) {
    r_walkers_[n][d] += gaussian_(rng_) * sqrt(dt_);
  }

  // Branching step
  double q = exp(- dt_ * (V(r_walkers_[n]) - E_T_));
  int survivors = static_cast<int>(q);
  if (q - survivors > uniform_(rng_)) {
    ++survivors;
  }

  // append survivors-1 copies of the walker to the end of the array
  for (int i = 0; i < survivors - 1; i++) {
    ensureCapacity(N_);
    for (int d = 0; d < DIM; d++) {
      r_walkers_[N_][d] = r_walkers_[n][d];
    }
    alive_[N_] = true;
    ++N_;
  }

  // if survivors is zero, then kill the walker
  if (survivors == 0) {
    alive_[n] = false;
  }
}

void DiffusionMC::oneTimeStep() {

  // DMC step for each walker
  int N_0 = N_;
  for (int n = 0; n < N_0; n++)
    oneMonteCarloStep(n);

  // remove all dead walkers from the arrays
  int newN = 0;
  for (int n = 0; n < N_; n++) {
    if (alive_[n]) {
      if (n != newN) {
	    for (int d = 0; d < DIM; d++) {
	      r_walkers_[newN][d] = r_walkers_[n][d];
        }
	    alive_[newN] = true;
      }
      ++newN;
    }
  }
  N_ = newN;

  // adjust E_T

  if ( N_ > 0 ) {
    E_T_ += log(N_T_ / double(N_)) / 10;
  }
  E_T_history_.push_back(E_T_);
    
  // measure energy, wave function
  E_sum_ += E_T_;
  E2_sum_ += E_T_ * E_T_;
  for (int n = 0; n < N_; n++) {
    double r2 = 0;
    for (int d = 0; d < DIM; d++) {
      r2 = r_walkers_[n][d] * r_walkers_[n][d];
    }
    int i = static_cast<int>(sqrt(r2) / r_max_ * NPSI);
    if (i < NPSI)
      psi_[i] += 1;
  }
}

void DiffusionMC::printout(std::ostream & out, int skip) {
  if (skip < 0) {
    skip = 1;
  }

  double dr = getRMax() / getNPSI();
  for (int i = 0; i < getNPSI(); i+=skip) {
    double r = i * dr;
    out << r << '\t' << psi_[i]  << std::endl;
  }    
       
}


void DiffusionMC::run(int n_time_steps) {
  std::cout  << "Running" << std::endl;
  
  // do 20% of timeSteps as thermalization steps
  int n_therm_steps = static_cast<int>(0.2 * n_time_steps);
  for (int i = 0; i < n_therm_steps; i++) {
    this->oneTimeStep();
  }

  std::cout << "Initialization after thermalizing" << std::endl;
  this->printout(std::cout,10);

  // production steps
  this->zeroAccumulators();
  for (int i = 0; i < n_time_steps; i++) {
    this->oneTimeStep();

    if ( i % 100 == 0 && i > 0 ) {
      std::cout << "i = " << i << ", Eavg = " << this->getESum() / i << std::endl;
    }
  }

  std::cout << "Final form" << std::endl;
  this->printout(std::cout,10);

  std::cout << "E_sum_ = " << this->getESum() << std::endl;
  std::cout << "E2_sum_ = " << this->getE2Sum() << std::endl;
    
  // compute averages
  double E_avg = this->getESum() / n_time_steps;
  double E_var = this->getE2Sum() / n_time_steps - E_avg * E_avg;
  std::cout << " <E> = " << E_avg << " +/- " << sqrt(E_var / n_time_steps) << std::endl;
  std::cout << " <E^2> - <E>^2 = " << E_var << std::endl;
  double psi_norm = 0;
  double psi_exact_norm = 0;
  double dr = this->getRMax() / this->getNPSI();
  for (int i = 0; i < this->getNPSI(); i++) {
    double r = i * dr;
    psi_norm += pow(r, this->getDIM()-1) * psi_[i] * psi_[i];
    psi_exact_norm += pow(r, this->getDIM()-1) * exp(- r * r);
  }
  psi_norm = sqrt(psi_norm);
  psi_exact_norm = sqrt(psi_exact_norm);

  for ( int i = 0; i < this->getNPSI(); ++i ){
    psi_[i] /= psi_norm; 
  }
  
}
