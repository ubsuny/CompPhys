#include "LorentzVector.h"


double LorentzVector::perp() const { return sqrt(perp2()); }
double LorentzVector::perp2() const { return x_*x_+y_*y_; }
double LorentzVector::mass() const { return sqrt(mass2()); }
double LorentzVector::mass2() const { return t_*t_ - x_*x_ - y_*y_ - z_*z_; }
double LorentzVector::p() const { return sqrt(perp2() + z_*z_); }
double LorentzVector::phi() const { return x_==0.0 && y_ == 0.0 ? 0.0 : atan2(y_,x_); }
double LorentzVector::theta() const { return  x_ == 0.0 && y_ == 0.0 && z_ == 0.0 ? 0.0 : atan2(perp(),z_); }
double LorentzVector::cosTheta() const {
  double mag = sqrt(x_*x_ + y_*y_ + z_*z_);
  return mag == 0. ? 1.0 : z_ / mag;
}
double LorentzVector::eta() const {
  double costheta = cosTheta();
  if (costheta*costheta < 1) return -0.5* log( (1.0-costheta)/(1.0+costheta) );
  if (z_ == 0.) return 0;
  if (z_ > 0.) return 10e10;
  else        return -10e10;
}

std::string LorentzVector::PrintPtEtaPhiM() const {
  std::stringstream ss;
  ss << "(pt,eta,phi,m) = (" << perp() << ", " << eta() << ", " << phi() << ", " << mass() << ")";
  return std::move(ss.str());
};
  
std::string LorentzVector::PrintPEtaPhiE() const {
  std::stringstream ss;
  ss << "(p,eta,phi,e) = (" << p() << ", " << eta() << ", " << phi() << ", " << e() << ")";
  return std::move(ss.str());
};
  
std::string LorentzVector::PrintXYZT() const {
  std::stringstream ss;
  ss << "(x,y,z,t) = (" << x_ << ", " << y_ << ", " << z_ << ", " << t_  << ")";
  return std::move(ss.str());
};

std::string LorentzVector::Print() const {
  std::stringstream ss;
  ss << PrintXYZT() << " " << PrintPEtaPhiE();
  return std::move(ss.str());
};
  
  
LorentzVector LorentzVector::operator+( const LorentzVector & right) const { return std::move( LorentzVector(x_+right.x_,y_+right.y_,z_+right.z_,t_+right.t_) ); }
LorentzVector LorentzVector::operator-( const LorentzVector & right) const { return std::move( LorentzVector(x_-right.x_,y_-right.y_,z_-right.z_,t_+right.t_) ); }
double LorentzVector::operator*(const LorentzVector & right) { return t_*right.t_ - x_*right.x_ - y_*right.y_ - z_*right.z_; }



void testLorentzVectors()
{
  
  std::cout << "Testing four vectors:" << std::endl;
  LorentzVector v1(1.0,0.0,0.0,1.0);
  LorentzVector v2(0.0,1.0,0.0,1.0);
  LorentzVector v3(0.0,0.0,1.0,1.0);

  std::cout << v1.Print() << std::endl;
  std::cout << v2.Print() << std::endl;
  std::cout << v3.Print() << std::endl;
  
  LorentzVector s1 = v1 + v2;
  LorentzVector s2 = v1 + v3;
  std::cout << s1.Print() << std::endl;
  std::cout << s2.Print() << std::endl;
}
