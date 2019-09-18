#ifndef Point3d_h
#define Point3d_h

#include <iostream>
#include <fstream>
#include "Point.h"

class Point3d : public Point {
 public:
  Point3d( double ix=0., double iy=0., double iz=0.);
  virtual ~Point3d();

  // Must be declared as a virtual override
  virtual void print(std::ostream & out=std::cout) const override;

  // x() and y() accessors are available through the base class Point
  double z() const;

  // Need to override all of these:
  Point3d operator+( Point3d const & right ) const ;
  Point3d operator-( Point3d const & right ) const ;
  Point3d & operator+=( Point3d const & right ) ;
  Point3d & operator-=( Point3d const & right ) ;

  // Must be declared as a virtual override
  virtual bool input( std::istream & in) override;

 private: 
  double z_;

  // Doubles x_ and y_ are in the base class!

};

#endif
