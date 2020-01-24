%module metropolis
/* First: Include your own code.*/
%{
#define SWIG_FILE_WITH_INIT
#include "metropolis.h"
#include "gaussian.h"
%}

%include "std_vector.i"

namespace std {
   %template(vector_double) vector<double>;
};

%include "metropolis.h"
%include "gaussian.h"
%template(gaussianD) gaussian<double>; 
%template(metropolisD) metropolis<gaussian<double>, double>;

