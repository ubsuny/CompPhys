#include "pimc.h"

using namespace std;

int main()
{
    cout << " Path Integral Monte Carlo for the Harmonic Oscillator\n"
         << " -----------------------------------------------------\n";

    // set simulation parameters
    double tau, delta, x_max;
    int M, n_bins, MC_steps;
    cout << " Imaginary time period tau = " << (tau = 10.0)
         << "\n Number of time slices M = " << (M = 100)
         << "\n Maximum displacement to bin x_max = " << (x_max = 4.0)
         << "\n Number of histogram bins in x = " << (n_bins = 100)
         << "\n Metropolis step size delta = " << (delta = 1.0)
         << "\n Number of Monte Carlo steps = " << (MC_steps = 100000)
         << endl;

    PathIntegralMC pimc(tau, M, n_bins, x_max,  delta, MC_steps);
    pimc.thermalize();    
    pimc.do_steps();

    return 0;
}
