#include <iostream>
unsigned int i = 1000;
int duh( void ) {
  static unsigned int count = 0;
  unsigned int i = 2;
  std::cout << "for the " << count << "th time, i = " << i << std::endl;
  ++count;
  return i;
}

int main(void){
  for ( unsigned int i = 10; i < 20; ++i ) {
    std::cout << "i = " << i << ", duh() = " << duh() << ", global i = " << ::i << std::endl;
  }
  return 0;
}
