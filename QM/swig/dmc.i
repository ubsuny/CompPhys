%module dmc
/* First: Include your own code.*/
%{
#define SWIG_FILE_WITH_INIT
#include "dmc.h"
%}

%include "std_vector.i"

namespace std {
   %template(vector_double) vector<double>;
};

%include "dmc.h"

