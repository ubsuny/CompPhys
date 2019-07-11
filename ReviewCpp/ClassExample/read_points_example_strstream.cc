#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "Point.h"

int main(void) {


  std::ifstream input("points.txt");

  std::vector<Point> points;

  while ( !input.eof() ) {



    std::string line;   
    std::getline( input, line, '\n');   


    if ( line == "") {      
      break;
    } 
    else {
      std::stringstream buf(line);

      std::string token;
      std::getline( buf, token, ',' );   
      double x =  std::atof( token.c_str() );
      std::getline( buf, token );   
      double y =  std::atof( token.c_str() );


      Point p(x,y);

      points.push_back(p);

    }

  }

  for( std::vector<Point>::const_iterator i = points.begin();
       i != points.end(); ++i ) {
    i->print();
  }


}
