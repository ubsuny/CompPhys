#include "root_finding.hpp"

using namespace std;

double f(double x) {
    return exp(x) * log(x) - x * x;
}
 
int main() {
    cout << " Algorithms for root of exp(x)*log(x) - x*x\n"
         << " ------------------------------------------------\n";
 
    cout << " 1. Simple search\n"
         << " Enter initial guess x_0, step dx, and desired accuracy: ";
    double x0, dx, acc;
    cin >> x0 >> dx >> acc;
    double answer = root_simple(f, x0, dx, acc,1000,true);
 
    cout << "\n\n"
         << " 2. Bisection search\n"
         << " Enter bracketing guesses x_1, x_2, and desired accuracy: ";
    double x1;
    cin >> x0 >> x1 >> acc;
    cout << " Answer = " << root_bisection(f, x0, x1, acc,1000,true) << endl;
}
