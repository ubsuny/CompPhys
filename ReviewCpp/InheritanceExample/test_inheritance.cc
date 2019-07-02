#include <iostream>
#include <vector>
#include "Point.h"
#include "Point3d.h"

int main(void) {


  Point xy(1,2);
  Point3d xyz(3,4,5);

  xy.print();
  xyz.print();

  std::vector<Point *> points = { &xy, &xyz};
  for ( auto const & point : points ) {
    point->print();
  }
  
};
