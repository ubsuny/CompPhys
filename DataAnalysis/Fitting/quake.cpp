#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "least_squares.hpp"

int main()
{
  using namespace std; 


    // data downloaded from http://neic.usgs.gov/neis/epic/epic_global.html
    const string quake_data("california_earthquakes_2010_to_2013.csv");

    cout << " Earthquake data: Gutenberg-Richter Law" << endl;

    // define a histogram to store the data
    int bins = 100;
    double M_min = 1.0, M_max = 10.0;
    double dM = (M_max - M_min) / bins;
    vector<double> M(bins), N(bins);
    for (int i = 0; i < bins; i++)
        M[i] = M_min + (i + 0.5) * dM;

    // read the data file and
    ifstream data_file(quake_data.c_str());
    if (data_file.fail()) {
        cerr << "cannot open " << quake_data << endl;
        exit(EXIT_FAILURE);
    } else
      cout << " reading data file: " << quake_data << endl;
    string line;
    int events = 0;
    while (getline(data_file, line)) {
        if (line.c_str()[0] != 't') {
	    //cout << "string is " << line << endl;

	    // The magnitude is stored in the fifth entry of the 
	    // comma-separated list. 
	    // Pick that out, convert to a double.
	    size_t found = 0;
	    string token(",");
	    for ( int ifound = 0; ifound < 4; ++ifound ) {
	      found = line.find(token, found+1);
	    }
	    size_t foundlast = line.find(token, found);
            string magnitudestr = line.substr(found+1, foundlast);
            double magnitude = atof(magnitudestr.c_str());         // atof <cstdlib>
	   
	    // Find the bin number for this magnitude
            int binnumber = int( floor( (magnitude - M_min) / dM ) );   // floor <cmath>

	    // For all of the bins *below* this bin, increment the histogram. 
            if (0 <= binnumber && binnumber < bins) {
	      for (int jlowerbins = 0; jlowerbins <= binnumber; ++jlowerbins, ++events)
                    N[jlowerbins] += 1;
            }
        }
    }
    data_file.close();
    cout << " stored " << events << " events in histogram" << endl;

    // some bins might have no events - log(N=0) = -infinity
    vector<double> M_values, log10N_values;
    for (int i = 0; i < bins; i++) {
        if (N[i] > 0) {
            M_values.push_back(M[i]);
            log10N_values.push_back(log10(N[i]));
        }
    }

    // write histogram to file for plotting
    ofstream histogram_file("histogram.dat");
    for (int i = 0; i < M_values.size(); i++)
        histogram_file << M_values[i] << '\t' << log10N_values[i] << '\n';
    histogram_file.close();
    cout << " wrote events to file: " << "histogram.dat" << endl;

    // fit histogram to straight line
    double a, b, sigma, sigma_a, sigma_b;
    least_squares(M_values, log10N_values, a, b, sigma, sigma_a, sigma_b);
    cout << " a = " << a << '\n' << " b = " << b << '\n'
         << " log_10(N) error bar = " << sigma << endl;
}
