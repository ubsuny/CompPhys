#ifndef Point_h
#define Point_h

#include <iostream>

class Point {
 public:
  Point( double ix=0., double iy=0.);
  ~Point();

  void print() const;

  double x() const;
  double y() const;

  Point operator+( Point const & right ) const;

  Point operator-( Point const & right ) const;

  Point & operator+=( Point const & right );

  Point & operator-=( Point const & right );

  bool input( std::istream & in); 

 private: 
  double x_;
  double y_; 

};

#endif
