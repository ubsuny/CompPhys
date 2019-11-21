#include "poisson_mg.h"
#include <fstream>
using namespace std;


int main()
{
  int L = 6, n_smooth=3;
  double accuracy = 1e-6;

  poisson_mg<double>::matrix_type rho;
  poisson_mg<double>::init_matrix( rho, L+2, L+2);

  poisson_mg<double> pmg(rho, accuracy, L, n_smooth);
  clock_t t0 = clock();
  pmg.execute();
  clock_t t1 = clock();
  cout << " CPU time = " << double(t1 - t0) / CLOCKS_PER_SEC
       << " sec" << endl;

  // write potential to file
  ofstream file("poisson_mg.data");
  for (int i = 0; i < L + 2; i++) {
    double x = i * pmg.get_h();
    for (int j = 0; j < L + 2; j++) {
      double y = j * pmg.get_h();
      file << x << '\t' << y << '\t' << pmg.get_psi()[i][j] << '\n';
    }
    file << '\n';
  }
  file.close();
  cout << " Potential in file poisson_mg.data" << endl;
}
