// Variational Monte Carlo for the harmonic oscillator
#include "vmc.h"

QHO::QHO(int Nin, double alphain, int MCStepsin) :
  rd(), gen(rd()), dis(0,1.), gausdev(),
  N(Nin), alpha(alphain), MCSteps(MCStepsin)
{
  x.resize(N);
  for (int i = 0; i < N; i++)
    x[i] = dis(gen)-0.5;
  delta = 1;

  nPsiSqd = int((xMax - xMin) / dx);
  psiSqd.resize(nPsiSqd);
  nAccept = 0;

  zeroAccumulators();
}

void QHO::zeroAccumulators() {
  eSum = eSqdSum = 0;
  for (int i = 0; i < nPsiSqd; i++)
    psiSqd[i] = 0;
}

double QHO::p(double xTrial, double x) {

  // compute the ratio of rho(xTrial) / rho(x)
  return exp(- 2 * alpha * (xTrial*xTrial - x*x));
}

double QHO::eLocal(double xi) {

  // compute the local energy
  return alpha + xi * xi * (0.5 - 2 * alpha * alpha);
}

void QHO::MetropolisStep() {

  // choose a walker at random
  int n = int(dis(gen) * N);

  // make a trial move
  double xTrial = x[n] + delta * gausdev(gen);

  // Metropolis test
  if (p(xTrial, x[n]) > dis(gen) ) {
    x[n] = xTrial;
    ++nAccept;
  }

  // accumulate energy and wave function
  double e = eLocal(x[n]);
  eSum += e;
  eSqdSum += e * e;
  int i = int((x[n] - xMin) / dx);
  if (i >= 0 && i < nPsiSqd)
    psiSqd[i] += 1;
}

void QHO::oneMonteCarloStep() {

  // perform N Metropolis steps
  for (int i = 0; i < N; i++) {
    MetropolisStep();
  }
}

void QHO::adjustStep() {
  // perform 20% of MCSteps as thermalization steps
  // and adjust step size so acceptance ratio ~50%
  int thermSteps = int(0.2 * MCSteps);
  int adjustInterval = int(0.1 * thermSteps) + 1;

  std::cout << " Performing " << thermSteps << " thermalization steps ..."
	    << std::flush;
  for (int i = 0; i < thermSteps; i++) {
    oneMonteCarloStep();
    if ((i+1) % adjustInterval == 0) {
      delta *= nAccept / (0.5 * N * adjustInterval) ;
      nAccept = 0;
    }
  }
  std::cout << "\n Adjusted Gaussian step size = " << delta << std::endl;    
}


// production steps
void QHO::doProductionSteps( ) {
  zeroAccumulators();
  nAccept = 0;
  std::cout << " Performing " << MCSteps << " production steps ..." << std::flush;
  for (int i = 0; i < MCSteps; i++)
    oneMonteCarloStep();
}

void QHO::printout() {

  // compute and print energy
  double eAve = get_eAve(); 
  double eVar = get_eVar(); 
  double error = sqrt(eVar) / sqrt(double(N) * MCSteps);
  std::cout << "\n <Energy> = " << eAve << " +/- " << error
	    << "\n Variance = " << eVar << std::endl;

}


void QHO::normPsi() {
  double psiNorm = 0;
  for (int i = 0; i < nPsiSqd; i++)
    psiNorm += psiSqd[i] * dx;
  for (int i = 0; i < nPsiSqd; i++) {
     psiSqd[i] /= psiNorm;
  }
}
