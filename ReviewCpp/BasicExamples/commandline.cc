#include <iostream>

int main(int argc, char * argv[] ){
  for ( unsigned int i = 0; i < argc; ++i ) {
    std::cout << "Argument " << i << " is " << argv[i] << std::endl;
  }
}
