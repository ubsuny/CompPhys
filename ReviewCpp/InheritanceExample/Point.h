#ifndef Point_h
#define Point_h

#include <iostream>
#include <fstream>

class Point {
 public:
  Point( double ix=0., double iy=0.);
  virtual ~Point();

  // To be overloaded in the base class
  virtual void print(std::ostream & out=std::cout) const;

  double x() const;
  double y() const;

  Point operator+( Point const & right ) const;

  Point operator-( Point const & right ) const;

  Point & operator+=( Point const & right );

  Point & operator-=( Point const & right );

  // To be overloaded in the base class
  virtual bool input( std::istream & in);

  // Now declared protected. 
 protected: 
  double x_;
  double y_; 

};

#endif
