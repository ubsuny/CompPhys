// Adapted from the MSTW2008 code file example.cc
// Needs mstwpdf.cc mstwpdf.h mstw2008lo.00.dat
// c++  mstw.cpp  mstwpdf.cc

#include <cmath>
#include <math.h>
#include <string>
#include <iostream>
#include <sstream>

#include "mstwpdf.h"
#include "LorentzVector.h"
#include "Particle.h"


// Calculate Drell-Yan cross section given initial quark momenta p1 and p2
double dSigmaDOmega( const Particle & p1, const Particle & p2, int pdgID_out, double cosTheta ) {
  if ( p1.pdgID() != -p2.pdgID() ) {
    std::cout << "Flavor changing neutral currents are not observed in the SM." << std::endl;
    return 0;
  }
  // Constants from http://pdg.lbl.gov/2014/reviews/rpp2014-rev-phys-constants.pdf
  static const double MZ = 91.1876;      // GeV
  static const double GF = 1.1663787e-5; // 1/GeV^2
  static const double sin2ThetaW = 0.23126;
  static const double Gamma_Z = 2.4952;

  double t3 = p1.t3();              // z-component of weak isospin of incoming particles
  double q = p1.q() ;               // charge of incoming particles
  auto tot = p1.p4() + p2.p4();     // p4 for the COM collision
  double s = tot.mass2();           // Mandelstam s (sqrt(s) = COM energy)
  double Nc_o = 1.;                 // Number of colors of outgoing particles
  double Nc_i = 1.;                 // Number of colors of incoming particles
  double q_o = -1.;                 // Charge of outgoing particles
  double t3_o = 0.;                 // Weak isospin of outgoing particles  
  getQ_T3_NC(pdgID_out, q_o, t3_o, Nc_o);

  // Compute some constants
  double c2 = 8*GF*MZ*MZ / sqrt(2);
  double L =    ( t3-sin2ThetaW*q);
  double R = -1*(sin2ThetaW*q);
  double Lp =  ( t3_o-sin2ThetaW*q_o);
  double Rp = -1*(sin2ThetaW*q_o);
  // L, R, Lp, Rp are correct
  double dsigma_domega =  Nc_o / ( Nc_i ) * s /( 256. * M_PI*M_PI) / ( pow( s-MZ*MZ, 2.0) + s* Gamma_Z*Gamma_Z) *
    c2*c2* ( (L*L+R*R)*(Lp*Lp+Rp*Rp)*(1+cosTheta*cosTheta) + (L*L-R*R)*(Lp*Lp-Rp*Rp)*2*cosTheta ) ;

  return dsigma_domega;
}

