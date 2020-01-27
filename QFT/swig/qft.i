%module qft


%include "std_vector.i"
%include "std_string.i"

/* First: Include your own code.*/
%{
#define SWIG_FILE_WITH_INIT
#include "LorentzVector.h"
#include "Particle.h"
#include "CrossSection.h"
#include "mstwpdf.h"
%}


namespace std {
   %template(vector_double) vector<double>;
};

%include "LorentzVector.h"
%include "Particle.h"
%include "CrossSection.h"
%include "mstwpdf.h"

