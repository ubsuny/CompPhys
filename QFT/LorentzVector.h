#ifndef LORENTZVECTOR_H
#define LORENTZVECTOR_H

#include <cmath>
#include <math.h>
#include <string>
#include <iostream>
#include <sstream>

// Minimal four-vector class
class LorentzVector{
  // Partially stolen from ROOT::TLorentzVector (https://root.cern.ch/doc/master/classTLorentzVector.html)
public:
  LorentzVector(double ix, double iy, double iz, double it) :
    x_(ix),y_(iy),z_(iz),t_(it){};

  inline double x() const { return x_;}
  inline double y() const { return y_;}
  inline double z() const { return z_;}
  inline double t() const { return t_;}
  inline double e() const { return t_;}  
  double perp() const ;
  double perp2() const ;
  double mass() const ;
  double mass2() const ;
  double p() const ;
  double phi() const ;
  double theta() const ;
  double cosTheta() const ;
  double eta() const ;

  std::string PrintPtEtaPhiM() const ;
  std::string PrintPEtaPhiE() const ;
  std::string PrintXYZT() const ;
  std::string Print() const ;
  
  
  LorentzVector operator+( const LorentzVector & right) const ;
  LorentzVector operator-( const LorentzVector & right) const ;
  double operator*(const LorentzVector & right) ;

  
protected :
  double x_;
  double y_;
  double z_;
  double t_;  

};


void testLorentzVectors();

#endif
