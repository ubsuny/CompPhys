#include "Particle.h"

void getQ_T3_NC(int pdgID, double & q, double & t3, double & NC)
{
  if ( std::abs(pdgID) < 7 ) NC = 3;
  else NC = 1;
  
  if       ( pdgID ==   2 || pdgID ==   4 || pdgID ==   6 ) { q = 2./3.; t3= 0.5;} // up type quark
  else if  ( pdgID ==  -2 || pdgID ==  -4 || pdgID ==  -6 ) { q =-2./3.; t3=-0.5;} // up type anti-quark
  else if  ( pdgID ==   1 || pdgID ==   3 || pdgID ==   5 ) { q =-1./3.; t3=-0.5;} // down type quark
  else if  ( pdgID ==  -1 || pdgID ==  -3 || pdgID ==  -5 ) { q = 1./3.; t3= 0.5;} // down type anti-quark
  else if  ( pdgID ==  11 || pdgID ==  13 || pdgID ==  15 ) { q = -1.0 ; t3=-0.5;} // charged leptons
  else if  ( pdgID == -11 || pdgID == -13 || pdgID == -15 ) { q =  1.0 ; t3= 0.5;} // charged leptons  
  else if  ( pdgID ==  12 || pdgID ==  14 || pdgID ==  16 ) { q =  0.0 ; t3= 0.5;} // neutrinos
  else if  ( pdgID == -12 || pdgID == -14 || pdgID == -16 ) { q =  0.0 ; t3=-0.5;} // anti-neutrinos  
  else {
    std::cout << "Error with PDG ID " << pdgID << std::endl;
    q = -9999; t3= -9999;
  }  
}
