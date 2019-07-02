#include "Point3d.h"


Point3d::Point3d( double ix, double iy, double iz) : Point(ix,iy), z_(iz) { 
}

Point3d::~Point3d(){}

void Point3d::print(std::ostream & out) const {
  out << "(" << x_ << "," << y_ << "," << z_ << ")" << std::endl;
};

double Point3d::z() const { return z_;}

Point3d Point3d::operator+( Point3d const & right ) const {
  Point3d retval( x_ + right.x_, y_ + right.y_, z_ + right.z_ );
  return retval;
}

Point3d Point3d::operator-( Point3d const & right ) const {
  Point3d retval( x_ - right.x_, y_ - right.y_, z_ - right.z_ );
  return retval;
}

Point3d & Point3d::operator+=( Point3d const & right )  {
  x_ += right.x_; y_ += right.y_ ; z_ += right.z_;
  return *this;
}

Point3d & Point3d::operator-=( Point3d const & right )  {
  x_ -= right.x_; y_ -= right.y_ ; z_ -= right.z_;
  return *this;
}

bool Point3d::input( std::istream & in ) {

    std::string line;
    std::getline( in, line, ',');   
    x_ = std::atof( line.c_str() ); 
    std::getline( in, line, ',' );   
    y_ = std::atof( line.c_str() );
    std::getline( in, line );
    z_ = std::atof( line.c_str() );
    if ( line == "") {      
       return false;  
    } 
    else {
       return true; 
    }
}
