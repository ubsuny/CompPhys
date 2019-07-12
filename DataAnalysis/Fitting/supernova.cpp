#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>
using namespace std;

// ---------------- declare global variables ----------------

string url("http://dark.dark-cosmology.dk/~tamarad/SN/");
string data_file_name("Davis07_R07_WV07.dat");
//string data_file_name("error1.dat");
//string data_file_name("error2.dat");
//string data_file_name("error3.dat");
//string data_file_name("error4.dat");

vector<double>               // C++ std template vector type
  z_data,                    // redshift - column 2 in data file
  mu_data,                   // distance modulus - column 3
  mu_err_data;               // error in distance modulus - column 4

// ---------------- function declarations ----------------

void read_data();            // opens and reads the data file

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

// ---------------- function definitions ----------------

int main() {

  cout << " Chi-square fit of supernova data to a straight line\n"
       << " Reference: " << url << endl;

  read_data();

  int n = z_data.size();
  vector<double> logz_data(n);
  for (int i = 0; i < n; i++)
    logz_data[i] = log10(z_data[i]);   // to use mu = a + b log_10(z)

  double intercept, slope, intercept_err, slope_err, chisqr;
  chi_square_fit(logz_data, mu_data, mu_err_data,
                 intercept, slope, intercept_err, slope_err, chisqr);

  cout.precision(4);
  cout << " slope = " << slope << " +- " << slope_err << "\n"
       << " intercept = " << intercept << " +- " << intercept_err << "\n"
       << " chi-square/d.o.f = " << chisqr / (n - 2) << endl;
}

void read_data() {

  // create an input file stream object and open the data file
  ifstream data_file(data_file_name.c_str());
  if (data_file.fail())
    cerr << "sorry, cannot open " << data_file_name << endl;

  // read the data file one line at a time
  string line;                         // string object to hold current line
  while (getline(data_file, line)) {   // std::getline defined in <string>

    if (line[0] == ';')                // skip lines starting with semicolon
      continue;

    string SN;                         // name of supernova in column 1
    double z, mu, mu_err;              // columns 2, 3, 4
    istringstream is(line);            // string stream object to read line
    is >> SN >> z >> mu >> mu_err;     // read successive column entries

    if (is.fail()) {                   // if a read error occurs
      cerr << "error reading line: "
           << line << endl;            // print an error message
      continue;
    }

    // store the data values in the data vectors
    z_data.push_back(z);
    mu_data.push_back(mu);
    mu_err_data.push_back(mu_err);
  }

  cout << " read " << z_data.size() << " data values" << endl;

  data_file.close();
}

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
