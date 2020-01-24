#include <iostream> 
#include "ising.h"


int main (int argc, char *argv[]) {

  int L;
  double T, H; 
  std::cout << " Two-dimensional Ising Model - Metropolis simulation\n"
	    << " ---------------------------------------------------\n"
	    << " Enter number of spins L in each direction: ";
  std::cin >> L;
  std::cout << " Enter temperature T: ";
  std::cin >> T;
  std::cout << " Enter magnetic field H: ";
  std::cin >> H;
  std::cout << " Enter number of Monte Carlo steps: ";
  int MCSteps;
  std::cin >> MCSteps;
  Ising ising(1.0, L, T, H);
  ising.run(MCSteps);

}
