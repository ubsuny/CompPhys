#include <fstream>
#include <iostream>
#include <string>


void input ( std::istream & in ) {
  std::string line;
  std::getline( in, line, ',');
  std::string firstname = line;
  std::getline( in, line, ',');
  std::string lastname = line;
  std::getline( in, line );
  int score = std::atof( line.c_str() );

  std::cout << "First name is " << firstname << std::endl;
  std::cout << "Last name is " << lastname << std::endl;
  std::cout << "Score is " << score << std::endl;
}


int main (void)
{

  std::cout << "Enter lastname,firstname,score:" << std::endl;
  input(std::cin);

  return 0; 
}
