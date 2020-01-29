%module reptation
/* First: Include your own code.*/
%{
#define SWIG_FILE_WITH_INIT
#include "reptation.h"
%}

%include "std_vector.i"
%include "std_deque.i"

namespace std {
   %template(vector_double) vector<double>;
   %template(deque_site) deque<Site>;
   %template(vector_deque_site) vector<deque<Site>>;
};

%include "reptation.h"

