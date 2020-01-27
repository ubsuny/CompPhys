#ifndef PARTICLE_H
#define PARTICLE_H

#include <cmath>
#include <math.h>
#include <string>
#include <iostream>
#include <sstream>
#include "LorentzVector.h"

void getQ_T3_NC(int pdgID, double & q, double & t3, double & NC);

class Particle{
public :
  Particle( LorentzVector const & p4, int pdgID ) :
    p4_(p4), pdgID_(pdgID)
  {
    double NC=0;
    getQ_T3_NC(pdgID, q_, t3_, NC);
  }

  inline const  LorentzVector & p4() const { return p4_;}
  inline double q() const { return q_;}
  inline double t3() const { return t3_;}
  inline int pdgID() const { return pdgID_; }
  
private :
  LorentzVector p4_; // 4-vector
  int pdgID_;     // PDG ID from http://pdg.lbl.gov/2007/reviews/montecarlorpp.pdf
  double q_;      // electric charge
  double t3_;     // weak isospin

};

#endif
