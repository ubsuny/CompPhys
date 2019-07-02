#ifndef STORAGE_H
#define STORAGE_H

#include "Point.h"

template<class T>
class Storage {
 public:
  
 Storage( T const & inval = T::T() ) : val_(inval) {}
  
  T const & get_val() const { return val_; }

 protected:
  T val_; 
};

typedef Storage<int> IntStorage;
typedef Storage<double> DoubleStorage;
typedef Storage<Point * > PointStorage;

#endif
