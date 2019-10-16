#include "scattering.h"

int main()
{

  using namespace std;
  cout << " Classical Scattering from Lennard-Jones potential" << endl;
  double E = 0.705;      // set global value of E
  cout << " Energy E = " << E << endl;
  double b_min = 0.6, db = 0.3;
  int n_b = 6;
  double b = 0.0;
  double V0 = 1.0;
  cout << " b      " << '\t' << "CrossSection(b)\n"
       << " -------" << '\t' << "--------" << endl;
  lennard_jones lj( V0 );
  for (int i = 0; i < n_b; i++) {

    stringstream sstream;
    sstream << "trajfile_cpp_" << i << ".data";
    ofstream file(sstream.str().c_str());

    b = b_min + i * db;
    std::vector< std::pair<double,double> > trajectory;
    CrossSection<lennard_jones> theta( lj, E, b, 3.5, 100 );
    double deflection = theta.calculate_trajectory(deflection);
    std::cout << " " << b << "\t\t" << deflection << std::endl;
    for (int i = 0; i < trajectory.size(); i++) {
      double r = trajectory[i].first;
      double theta = trajectory[i].second;
      char buff[1000];
      sprintf(buff, "%8.4f %8.4f", r*cos(theta), r*sin(theta));
      file << buff << std::endl;
    }
    file << std::endl;

    file.close();
  }

}
