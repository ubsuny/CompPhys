// Adapted from the MSTW2008 code file example.cc
// Needs mstwpdf.cc mstwpdf.h mstw2008lo.00.dat
// c++  mstw.cpp  mstwpdf.cc
#ifndef CrossSection_h
#define CrossSection_h

#include <cmath>
#include <math.h>
#include <string>
#include <iostream>
#include <sstream>

#include "mstwpdf.h"
#include "LorentzVector.h"
#include "Particle.h"


// Calculate Drell-Yan cross section given initial quark momenta p1 and p2
double dSigmaDOmega( const Particle & p1, const Particle & p2, int pdgID_out, double cosTheta );

#endif
