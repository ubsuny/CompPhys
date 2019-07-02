#include "Point.h"


Point::Point( double ix, double iy) { 
  x_=ix;y_=iy;
}

Point::~Point(){}

void Point::print() const {
  std::cout << "(" << x_ << "," << y_ << ")" << std::endl;
};

double Point::x() const { return x_;}
double Point::y() const { return y_;}

Point Point::operator+( Point const & right ) const {
  Point retval( x_ + right.x_, y_ + right.y_ );
  return retval;
}

Point Point::operator-( Point const & right ) const {
  Point retval( x_ - right.x_, y_ - right.y_ );
  return retval;
}

Point & Point::operator+=( Point const & right )  {
  x_ += right.x_; y_ += right.y_ ;
  return *this;
}

Point & Point::operator-=( Point const & right )  {
  x_ -= right.x_; y_ -= right.y_ ;
  return *this;
}

bool Point::input( std::istream & in ) {

  std::string line;   
  std::getline( in, line, ',');   
  x_ = std::atof( line.c_str() ); 
  std::getline( in, line );   
  y_ = std::atof( line.c_str() );       
  if ( line == "") {      
    return false;  
  } 
  else {
    return true; 
  }
}
