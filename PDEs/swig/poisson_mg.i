%module poisson_mg
%{
#include "poisson_mg.h"
%}

%include "std_vector.i"

namespace std {
   %template(vector_type_d) vector< double>;
   %template(matrix_type_d) vector< vector<double> >;
};

%include "poisson_mg.h"

%template(poisson_mg_double) poisson_mg<double>;
