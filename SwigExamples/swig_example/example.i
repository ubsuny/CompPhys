%module example
/* First: Include your own code.*/
%{
#define SWIG_FILE_WITH_INIT
#include "example.hpp"
%}
/* Next: declare the functions you want to use.*/
int sum_int(std::vector<int> const & vec);

/* Finally: include any other libraries and types you need. 
Yes, you need one type per class, so that means one type per
template instance.*/


%include "std_vector.i"

namespace std {
   %template(vector_int) vector<int>;
};


