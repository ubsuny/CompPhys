%module vmc
/* First: Include your own code.*/
%{
#define SWIG_FILE_WITH_INIT
#include "vmc.h"
%}

%include "std_vector.i"

namespace std {
   %template(vector_double) vector<double>;
};

%include "vmc.h"

