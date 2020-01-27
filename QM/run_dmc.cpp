
#include "dmc.h"
using namespace std;

int main() {

  std::cout << "Hello!" << std::endl;
  double dt = 0.1;
  int N_T = 100, timeSteps = 1000;
  
  DiffusionMC dmc(N_T,dt);
  std::cout << "About to run" << std::endl;
  dmc.run(timeSteps); 

}
