%module scattering
/* First: Include your own code.*/
%{
#define SWIG_FILE_WITH_INIT
#include "scattering.h"
%}

%include "std_vector.i"
%include "std_pair.i"

namespace std {
  %template(pair_double) pair<double,double>;
  %template(trajectory) vector< std::pair<double,double> >;
};


%include "scattering.h"
%template(CrossSection_hard_sphere_potential) CrossSection<hard_sphere_potential>;
%template(CrossSection_lennard_jones) CrossSection<lennard_jones>;

  
