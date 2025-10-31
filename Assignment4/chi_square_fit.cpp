#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>
using namespace std;


void chi_square_fit(         // makes a linear chi-square fit
  const vector<double>& x,   // vector of x values - input
  const vector<double>& y,   // vector of y values - input
  const vector<double>& err, // vector of y error values - input
  double& a,                 // fitted intercept - output
  double& b,                 // fitted slope - output
  double& sigma_a,           // estimated error in intercept - output
  double& sigma_b,           // estimated error in slope - output
  double& chi_square         // minimized value of chi-square sum - output
);

void chi_square_fit(         // makes a linear chi-square fit
  const vector<double>& x,   // vector of x values - input
  const vector<double>& y,   // vector of y values - input
  const vector<double>& err, // vector of y error values - input
  double& a,                 // fitted intercept - output
  double& b,                 // fitted slope - output
  double& sigma_a,           // estimated error in intercept - output
  double& sigma_b,           // estimated error in slope - output
  double& chi_square)        // minimized value of chi-square sum - output
{
  int n = x.size();

  assert(n >= 2);

  double S = 0, S_x = 0, S_y = 0;
  for (int i = 0; i < n; i++) {
    assert ( fabs(err[i]) >= 0.000001 );
    S += 1 / err[i] / err[i];
    S_x += x[i] / err[i] / err[i];
    S_y += y[i] / err[i] / err[i];
  }

  vector<double> t(n);
  for (int i = 0; i < n; i++)
    t[i] = (x[i] - S_x/S) / err[i];

  double S_tt = 0;
  for (int i = 0; i < n; i++)
    S_tt += t[i] * t[i];

  b = 0;
  for (int i = 0; i < n; i++)
    b += t[i] * y[i] / err[i];
  assert( fabs(S_tt) > 0.00001);
  b /= S_tt;

  assert( fabs(S) > 0.00001);
  a = (S_y - S_x * b) / S;
  sigma_a = sqrt((1 + S_x * S_x / S / S_tt) / S);
  sigma_b = sqrt(1 / S_tt);

  chi_square = 0;
  for (int i = 0; i < n; i++) {
    double diff = (y[i] - a - b * x[i]) / err[i];
    chi_square += diff * diff;
  }
}
