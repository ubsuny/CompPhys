#include <cmath>
#include <iostream>
using namespace std;

const int n = 24;   // number of galaxies in Table 1

double r[n] = {     // distances in Mpc
  0.032, 0.034, 0.214, 0.263, 0.275, 0.275, 0.45, 0.5, 0.5, 0.63, 0.8, 0.9,
  0.9,   0.9,   0.9,   1.0,   1.1,   1.1,   1.4,  1.7, 2.0, 2.0,  2.0, 2.0
};

double v[n] = {     // velocities in km/s
  +170, +290, -130, -70,  -185, -220, +200, +290, +270, +200, +300, -30,
  +650, +150, +500, +920, +450, +500, +500, +960, +500, +850, +800, +1090
};

int main() {

  // declare and initialize various sums to be computed
  double s_x = 0, s_y = 0, s_xx = 0, s_xy = 0;

  if ( n < 2 ) {
    cout << "Error! Need at least two data points!" << endl;
    return 0;
  }

  // compute the sums
  for (int i = 0; i < n; i++) {
    s_x += r[i];
    s_y += v[i];
    s_xx += r[i] * r[i];
    s_xy += r[i] * v[i];
  }

  cout << s_x << " " << s_y << " " << s_xx << " " << s_xy << endl;

  // evaluate least-squares fit forumlas
  double denom = n * s_xx - s_x * s_x;
 
  if ( fabs(denom) < 0.000001 ) {
    cout << "Error! Denominator is zero!" << endl;
    return 0;
  }

  double a = (s_xx * s_y - s_x * s_xy) / denom;
  double b = (n * s_xy - s_x * s_y) / denom;

  cout << denom << " " << a << " " << b << endl;

  // estimate the variance in the data set
  double sum = 0;
  for (int i = 0; i < n; i++) {
    double v_of_r_i = a + b * r[i];
    double error = v[i] - v_of_r_i;
    sum += error * error;
  }

  double sigma = (n > 2) ? sqrt(sum / (n - 2)) : 0;    // estimate of error bar in v

  // estimate errors in a and b
  double sigma_a = sqrt(sigma * sigma * s_xx / denom);
  double sigma_b = sqrt(sigma * sigma * n / denom);

  // print results
  cout.precision(4);
  cout << " Least-squares fit of " << n << " data points\n"
       << " -----------------------------------\n"
       << " Hubble's constant slope   b  =  " << b
       << " +- " << sigma_b << " km/s/Mpc\n"
       << " Intercept with r axis     a  =  " << a
       << " +- " << sigma_a << " km/s\n"
       << " Estimated v error bar sigma  =  " << sigma << " km/s" << endl;
}
