#include <iostream>
#include <fstream>
#include <vector>
#include "Point.h"


// Pass a pointer to a vector of points to a function to print them all
void print_all_points( std::vector<Point> * thisisastupidname ) {
  // Say we picked option 2: Now print!
  double average = 0.;
  for ( unsigned int i = 0; i < thisisastupidname->size(); ++i ) {
    (*thisisastupidname)[i].print();
    average += (*thisisastupidname)[i].x();
  }
  average /= thisisastupidname->size();
  std::cout << "The average is " << average << std::endl;
}



int main(int argc, char ** argv) {


  std::ifstream inputfile( "points.txt");
  std::vector<Point> p_vector;  

  // Now LOOP!
  bool valid = true;
  while( valid ) {
    Point p1;
    valid = p1.input( inputfile ) ;
    if ( not valid ) 
      break;
    std::cout << "You input:" << std::endl;
    p1.print();
    p_vector.push_back( p1 );
    
  }

  std::cout << "Printing all points!" << std::endl;
  print_all_points( &p_vector); // make sure to pass the address!!
  return 0;
}
