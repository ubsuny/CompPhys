#include "vmc.h"

int main() {
  
  int N=10; double alpha=0.2; int MCSteps=10000;
  
  QHO qho(N,alpha,MCSteps);
  qho.adjustStep();
  qho.doProductionSteps();  
  qho.print();

}
