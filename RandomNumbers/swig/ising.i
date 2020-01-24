%module ising
/* First: Include your own code.*/
%{
#define SWIG_FILE_WITH_INIT
#include "ising.h"
%}

%include "std_vector.i"

namespace std {
   %template(vector_double) vector<double>;
};

%include "ising.h"


