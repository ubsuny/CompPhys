#include <iostream>
#include "Point.h"

int main(int argc, char ** argv) {


  Point p1(0.,1.);
  Point p2(2.,3.);
  std::cout << "p1: (" << p1.x() << "," << p1.y() << ")" << std::endl;
  std::cout << "p2: (" << p2.x() << "," << p2.y() << ")" << std::endl;
  Point * p = &p1;
  std::cout << "p : (" << p->x() << "," << p->y() << ")" << std::endl;

  std::cout << "p1: ";
  p1.print();
  std::cout << "p2: ";
  p2.print();  
  std::cout << "p : ";
  p->print();

  Point sum = p1 + p2;
  Point dif = p1 - p2;

  sum += p1;
  dif -= p2; 
  std::cout << "Sum: ";
  sum.print();
  std::cout << "Dif: ";
  dif.print();

  return 0;
}
