
#include "ising.h"



Ising::Ising(double iJ, int iL, int iN_flips_per_step, double iT, double iH) :
  rd_(), rng_(rd_()), uniform_(0, 1.),
  J_(iJ), L_(iL), Lx_(iL), Ly_(iL),  N_spins_(Lx_ * Ly_), 
  N_flips_per_step_(iN_flips_per_step), T_(iT), H_(iH), thermalized_(false)
{
  spins_.resize(Lx_);
  for (int i = 0; i < Lx_; i++){
    spins_[i].resize(Ly_);
    for (int j = 0; j < Ly_; j++)
      spins_[i][j] =  uniform_(rng_) < 0.5 ? +1 : -1;   // hot start
  }
  computeBoltzmannFactors();
  steps_ = 0;

  resetAverages();
}

void Ising::thermalize(unsigned int n_therm) {
  for (unsigned int i = 0; i < n_therm; i++) {
    oneMCStepPerSpin();
  }

}

void Ising::resetAverages(){
  mAv_ = 0;
  m2Av_ = 0; 
  eAv_ = 0;
  e2Av_ = 0;
  m_vals_.clear();
  E_vals_.clear(); 
}
  
void Ising::computeBoltzmannFactors()
{
  for (int i = -8; i <= 8; i += 4) {
    w_[i + 8][0] = exp( - (i * J_ - 2 * H_) / T_);
    w_[i + 8][2] = exp( - (i * J_ + 2 * H_) / T_);
  }
}

bool Ising::metropolisStep()
{
  // choose a random spin
  int i = int(Lx_ * uniform_(rng_));
  int j = int(Ly_ * uniform_(rng_));

  // find its neighbors using periodic boundary conditions
  int iPrev = i == 0 ? Lx_-1 : i-1;
  int iNext = i == Lx_-1 ? 0 : i+1;
  int jPrev = j == 0 ? Ly_-1 : j-1;
  int jNext = j == Ly_-1 ? 0 : j+1;

  // find sum of neighbors
  int sum_neighbors = spins_[iPrev][j] + spins_[iNext][j] + spins_[i][jPrev] + spins_[i][jNext];
  int delta_ss = 2 * spins_[i][j] * sum_neighbors;

  // ratio of Boltzmann factors
  double ratio = w_[delta_ss+8][1+spins_[i][j]];
  if (uniform_(rng_) < ratio) {
    spins_[i][j] = -spins_[i][j];
    return true;
  } else {
    return false;
  }
}

void Ising::oneMCStepPerSpin() {
  int accepts = 0;
  for (int i = 0; i < N_flips_per_step_; i++) {
    if (metropolisStep()) {
      ++accepts;
    }
  }
  acceptance_ratio_ = accepts / double(N_flips_per_step_);
  ++steps_;
}

double Ising::magnetizationPerSpin() {
  int sSum = 0;
  for (int i = 0; i < Lx_; i++)
    for (int j = 0; j < Ly_; j++) {
      sSum += spins_[i][j];
    }
  return sSum / double(N_spins_);
}

double Ising::energyPerSpin ( ) {
  int sSum = 0;
  int ssSum = 0;
  for (int i = 0; i < Lx_; i++)
    for (int j = 0; j < Ly_; j++) {
      sSum += spins_[i][j];
      int iNext = i == Lx_-1 ? 0 : i+1;
      int jNext = j == Ly_-1 ? 0 : j+1;
      ssSum += spins_[i][j]*(spins_[iNext][j] + spins_[i][jNext]);
    }
  return -(J_ * ssSum + H_ * sSum) / N_spins_;
}

void Ising::run(int n_mc_steps){
  //std::cout << " Done\n Performing production steps ..." << std::flush;
  resetAverages();
  for (int i_step = 0; i_step < n_mc_steps; i_step++) {
    this->oneMCStepPerSpin();
    double m = this->magnetizationPerSpin();
    double e = this->energyPerSpin();
    mAv_ += m; 
    m2Av_ += m * m;
    eAv_ += e; 
    e2Av_ += e * e;
    m_vals_.push_back(m);
    E_vals_.push_back(e);
  }
  mAv_ /= n_mc_steps; 
  m2Av_ /= n_mc_steps;
  eAv_ /= n_mc_steps; 
  e2Av_ /= n_mc_steps;
  //std::cout << " <m> = " << mAv << " +/- " << sqrt(m2Av - mAv*mAv) << std::endl;
  //std::cout << " <e> = " << eAv << " +/- " << sqrt(e2Av - eAv*eAv) << std::endl;
    
}

