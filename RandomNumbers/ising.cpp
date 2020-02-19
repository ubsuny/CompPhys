
#include "ising.h"



Ising::Ising(double iJ, int iL, int iN, double iT, double iH) :
  rd(), gen(rd()), dis(0,1.),
  J(iJ), L(iL), Lx(L), Ly(L), N(iN), T(iT), H(iH)
{
  s.resize(Lx);
  for (int i = 0; i < Lx; i++){
    s[i].resize(Ly);
    for (int j = 0; j < Ly; j++)
      s[i][j] =  dis(gen) < 0.5 ? +1 : -1;   // hot start
  }
  compute_boltzmann_factors();
  steps = 0;

  reset_averages();
}


void Ising::reset_averages(){
  mAv = 0;
  m2Av = 0; 
  eAv = 0;
  e2Av = 0;
  mvals.clear();
  evals.clear(); 
}
  
void Ising::compute_boltzmann_factors()
{
  for (int i = -8; i <= 8; i += 4) {
    w[i + 8][0] = exp( - (i * J - 2 * H) / T);
    w[i + 8][2] = exp( - (i * J + 2 * H) / T);
  }
}

bool Ising::metropolis_step()
{
  // choose a random spin
  int i = int(Lx * dis(gen));
  int j = int(Ly * dis(gen));

  // find its neighbors using periodic boundary conditions
  int iPrev = i == 0 ? Lx-1 : i-1;
  int iNext = i == Lx-1 ? 0 : i+1;
  int jPrev = j == 0 ? Ly-1 : j-1;
  int jNext = j == Ly-1 ? 0 : j+1;

  // find sum of neighbors
  int sumNeighbors = s[iPrev][j] + s[iNext][j] + s[i][jPrev] + s[i][jNext];
  int delta_ss = 2*s[i][j]*sumNeighbors;

  // ratio of Boltzmann factors
  double ratio = w[delta_ss+8][1+s[i][j]];
  if (dis(gen) < ratio) {
    s[i][j] = -s[i][j];
    return true;
  } else return false;
}

void Ising::one_monte_carlo_step_per_spin ( ) {
  int accepts = 0;
  for (int i = 0; i < N; i++)
    if (metropolis_step())
      ++accepts;
  acceptanceRatio = accepts/double(N);
  ++steps;
}

double Ising::magnetizationPerSpin ( ) {
  int sSum = 0;
  for (int i = 0; i < Lx; i++)
    for (int j = 0; j < Ly; j++) {
      sSum += s[i][j];
    }
  return sSum / double(N);
}

double Ising::energyPerSpin ( ) {
  int sSum = 0, ssSum = 0;
  for (int i = 0; i < Lx; i++)
    for (int j = 0; j < Ly; j++) {
      sSum += s[i][j];
      int iNext = i == Lx-1 ? 0 : i+1;
      int jNext = j == Ly-1 ? 0 : j+1;
      ssSum += s[i][j]*(s[iNext][j] + s[i][jNext]);
    }
  return -(J*ssSum + H*sSum)/N;
}

void Ising::run(int MCSteps){
  int thermSteps = int(0.2 * MCSteps);
  //std::cout << " Performing " << thermSteps
  //	    << " steps to thermalize the system ..." << std::flush;
  for (int s = 0; s < thermSteps; s++)
    one_monte_carlo_step_per_spin();

  //std::cout << " Done\n Performing production steps ..." << std::flush;
  reset_averages();
  for (int s = 0; s < MCSteps; s++) {
    this->one_monte_carlo_step_per_spin();
    double m = this->magnetizationPerSpin();
    double e = this->energyPerSpin();
    mAv += m; m2Av += m * m;
    eAv += e; e2Av += e * e;
    mvals.push_back(m);
    evals.push_back(e);
  }
  mAv /= MCSteps; m2Av /= MCSteps;
  eAv /= MCSteps; e2Av /= MCSteps;
  //std::cout << " <m> = " << mAv << " +/- " << sqrt(m2Av - mAv*mAv) << std::endl;
  //std::cout << " <e> = " << eAv << " +/- " << sqrt(e2Av - eAv*eAv) << std::endl;
    
}

