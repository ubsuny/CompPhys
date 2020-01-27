// Diffusion Monte Carlo program for the 3-D harmonic oscillator
#include "dmc.h"

using namespace std;



  
DiffusionMC::DiffusionMC(int nt, double idt) :
  rd(), gen(rd()), dis(0,1.), gausdev(),
  N_T(nt), dt(idt)
{
  std::cout << "Hello from DiffusionMC" << std::endl;
  N = N_T;                   // set N to target number specified by user
  ensureCapacity(N);    
  for (int n = 0; n < N; n++) {      
    for (int d = 0; d < DIM; d++)
      r[n][d] = dis(gen)- 0.5;
    alive[n] = true;
  }
  zeroAccumulators();
  E_T = 0;                   // initial guess for the ground state energy

}



double DiffusionMC::V( std::vector<double> const & r) {          // harmonic oscillator in DIM dimensions
  double rSqd = 0;
  for (int d = 0; d < DIM; d++)
    rSqd += r[d] * r[d];
  return 0.5 * rSqd;
}

void DiffusionMC::ensureCapacity(int index) {

  if (index < r.size())          // no need to expand array
    return;                // do nothing
  else {
    r.resize( 2 * index, std::vector<double> (DIM) );      
    alive.resize( 2 * index, false );      
    return;
  }
}
  
void DiffusionMC::zeroAccumulators() {
  ESum = ESqdSum = 0;
  psi.clear();
  psi.resize(NPSI);
}


void DiffusionMC::oneMonteCarloStep(int n) {

  // Diffusive step
  for (int d = 0; d < DIM; d++)
    r[n][d] += gausdev(gen) * sqrt(dt);

  // Branching step
  double q = exp(- dt * (V(r[n]) - E_T));
  int survivors = static_cast<int>(q);
  if (q - survivors > dis(gen))
    ++survivors;

  // append survivors-1 copies of the walker to the end of the array
  for (int i = 0; i < survivors - 1; i++) {
    ensureCapacity(N);
    for (int d = 0; d < DIM; d++)
      r[N][d] = r[n][d];
    alive[N] = true;
    ++N;
  }

  // if survivors is zero, then kill the walker
  if (survivors == 0)
    alive[n] = false;
}

void DiffusionMC::oneTimeStep() {

  // DMC step for each walker
  int N_0 = N;
  for (int n = 0; n < N_0; n++)
    oneMonteCarloStep(n);

  // remove all dead walkers from the arrays
  int newN = 0;
  for (int n = 0; n < N; n++)
    if (alive[n]) {
      if (n != newN) {
	for (int d = 0; d < DIM; d++)
	  r[newN][d] = r[n][d];
	alive[newN] = true;
      }
      ++newN;
    }
  N = newN;

  // adjust E_T

  if ( N > 0 )
    E_T += log(N_T / double(N)) / 10;

  // measure energy, wave function
  ESum += E_T;
  ESqdSum += E_T * E_T;
  for (int n = 0; n < N; n++) {
    double rSqd = 0;
    for (int d = 0; d < DIM; d++)
      rSqd = r[n][d] * r[n][d];
    int i = static_cast<int>(sqrt(rSqd) / rMax * NPSI);
    if (i < NPSI)
      psi[i] += 1;
  }

}

void DiffusionMC::printout(std::ostream & out, int skip) {
  if ( skip < 0 )
    skip = 1;

  double dr = getRMax() / getNPSI();
  for (int i = 0; i < getNPSI(); i+=skip) {
    double r = i * dr;
    out << r << '\t' << psi[i]  << std::endl;
  }    
       
}


void DiffusionMC::run( int timeSteps )
{
  std::cout  << "Running" << std::endl;
  
  // do 20% of timeSteps as thermalization steps
  int thermSteps = static_cast<int>(0.2 * timeSteps);
  for (int i = 0; i < thermSteps; i++)
    this->oneTimeStep();

  std::cout << "Initialization after thermalizing" << std::endl;
  this->printout(std::cout,10);

    
  // production steps
  this->zeroAccumulators();
  for (int i = 0; i < timeSteps; i++) {
    this->oneTimeStep();

    if ( i % 100 == 0 && i > 0 ) {
      std::cout << "i = " << i << ", Eavg = " << this->getESum() / i << std::endl;
    }
  }

  std::cout << "Final form" << std::endl;
  this->printout(std::cout,10);

  std::cout << "ESum = " << this->getESum() << std::endl;
  std::cout << "ESqdSum = " << this->getESqdSum() << std::endl;
    
  // compute averages
  double EAve = this->getESum() / timeSteps;
  double EVar = this->getESqdSum() / timeSteps - EAve * EAve;
  cout << " <E> = " << EAve << " +/- " << sqrt(EVar / timeSteps) << endl;
  cout << " <E^2> - <E>^2 = " << EVar << endl;
  double psiNorm = 0, psiExactNorm = 0;
  double dr = this->getRMax() / this->getNPSI();
  for (int i = 0; i < this->getNPSI(); i++) {
    double r = i * dr;
    psiNorm += pow(r, this->getDIM()-1) * psi[i] * psi[i];
    psiExactNorm += pow(r, this->getDIM()-1) * exp(- r * r);
  }
  psiNorm = sqrt(psiNorm);
  psiExactNorm = sqrt(psiExactNorm);

  for ( int i = 0; i < this->getNPSI(); ++i ){
    psi[i] /= psiNorm; 
  }
  
}
