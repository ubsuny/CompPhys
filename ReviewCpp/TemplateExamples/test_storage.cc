#include <iostream>
#include "Storage.h"

int main(void) {



  Storage<int> intstorage( 5 );
  Storage<double> doublestorage( 4.6);



  std::cout << "Int storage: " << intstorage.get_val() << std::endl;
  std::cout << "double storage: " << doublestorage.get_val() << std::endl;


  double x,y;
  std::cout << "Enter x and y:" << std::endl;
  std::cin >> x >> y;
  Point p(x,y);
  Storage<Point * >  sp( &p );

  std::cout << "Point storage: " ;
  sp.get_val()->print(std::cout);
  
};
