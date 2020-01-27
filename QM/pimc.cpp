// Path Integral Monte Carlo program for the 1-D harmonic oscillator

#include "pimc.h"

PathIntegralMC::PathIntegralMC(double itau, int iM, int inbins, double ixmax, double idelta, int iMC_steps):
  rd(), gen(rd()), dis(0,1.), gausdev(),
  tau(itau),M(iM),Delta_tau(tau/M),n_bins(inbins),x_min(-ixmax),x_max(ixmax),x_new(0),dx((x_max - x_min) / n_bins),delta(idelta),MC_steps(iMC_steps)
{
  x.resize(M);
  P.resize(n_bins);
  for (int j = 0; j < M; ++j)
    x[j] = (2 * dis(gen) - 1) * x_max;
}

  
double PathIntegralMC::V(double x)          // potential energy function
{
  // use units such that m = 1 and omega_0 = 1
  return 0.5 * pow(x, 2.0);
}

double PathIntegralMC::dVdx(double x)       // derivative dV(x)/dx used in virial theorem
{
  return x;
}

int PathIntegralMC::thermalize()
{
  int therm_steps = MC_steps / 5, acceptances = 0;
  x_new = 0;
  for (int step = 0; step < therm_steps; ++step)
    for (int j = 0; j < M; ++j)
      if (Metropolis_step_accepted())
	++acceptances;
  return acceptances;
}

void PathIntegralMC::do_steps()
{
  double E_sum = 0, E_sqd_sum = 0;    
  int acceptances = 0;
  P.clear();
  P.resize(n_bins);
  for (int step = 0; step < MC_steps; ++step) {
    for (int j = 0; j < M; ++j) {
      if (Metropolis_step_accepted())
	++acceptances;
      // add x_new to histogram bin
      int bin = int((x_new - x_min) / (x_max - x_min) * n_bins);
      if (bin >= 0 && bin < M)
	P[bin] += 1;
      // compute Energy using virial theorem formula and accumulate
      double E = V(x_new) + 0.5 * x_new * dVdx(x_new);
      E_sum += E;
      E_sqd_sum += E * E;
    }
  }

  // compute averages
  double values = MC_steps * M;
  E_ave = E_sum / values;
  E_var = E_sqd_sum / values - E_ave * E_ave;
  E_ave = 0;
  for (int bin = 0; bin < n_bins; ++bin) {
    double x = x_min + dx * (bin + 0.5);
    E_ave += P[bin] / values * (0.5 * x * dVdx(x) + V(x));
  }

}
    

bool PathIntegralMC::Metropolis_step_accepted()
{
  // choose a time slice at random
  int j = int(dis(gen) * M);
  // indexes of neighbors periodic in tau
  int j_minus = j - 1, j_plus = j + 1;
  if (j_minus < 0) j_minus = M - 1;
  if (j_plus > M - 1) j_plus = 0;
  // choose a random trial displacement
  double x_trial = x[j] + (2 * dis(gen) - 1) * delta;
  // compute change in energy
  double Delta_E = V(x_trial) - V(x[j])
    + 0.5 * pow((x[j_plus] - x_trial) / Delta_tau, 2.0)
    + 0.5 * pow((x_trial - x[j_minus]) / Delta_tau, 2.0)
    - 0.5 * pow((x[j_plus] - x[j]) / Delta_tau, 2.0)
    - 0.5 * pow((x[j] - x[j_minus]) / Delta_tau, 2.0);
  if (Delta_E < 0.0 || exp(- Delta_tau * Delta_E) > dis(gen)) {
    x_new = x[j] = x_trial;
    return true;
  } else {
    x_new = x[j];
    return false;
  }
}
