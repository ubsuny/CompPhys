#include <fstream>
#include <iostream>

int main(void){

  std::ifstream  in("inputfile.txt");
  std::ofstream  out("myfile.txt");
  double d;
  in >> d;
  out << d;
  out.close();

  return 0;
}
