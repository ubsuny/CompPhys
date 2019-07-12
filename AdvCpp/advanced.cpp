#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>


// Make a class to demonstrate smart and dumb copying.
class A{
protected:
  // Data for the class is just a vector<int>
  std::vector<int> v_;
public:
  // Declare an iterator type for convenience. 
  typedef decltype(v_)::iterator iterator;

  // Make an initializer with an int to start the vector off.
  A(unsigned int n) : v_(n) {}
  
  // Make the "Rule of 5":
  //  Copy constructor
  //  Move constructor
  //  Copy =
  //  Move =
  //  Destructor
  A( A const & ia) : v_(ia.v_) {}
  A( A && ia ) noexcept  {  std::swap( v_, ia.v_); }
  A & operator=(A const & ia)  { v_=ia.v_; return *this; }
  A & operator=(A && ia) noexcept { std::swap( v_,ia.v_); return *this; }
  ~A() {}

  // Write a couple of easy accessors to the internal vector v_
  iterator begin() { return v_.begin(); }
  iterator end()   { return v_.end(); }
  

};

int main(int argc, char ** argv){

  if ( argc < 2 ){
    std::cout << "enter a number on the command line" << std::endl;
    return 0;
  }

  // Initialize our objects to n ints
  unsigned int n = std::atoi( argv[1] );
  A data1(n);
  A data2(n);
  // Just fill with something nontrivial
  A::iterator i = data1.begin(), j=data2.begin();
  int ndx=0;
  for ( ; i != data1.end(); ++i, ++j, ++ndx) {
    *i = ndx;
    *j = n - ndx;
  }

  // Swap by copy (three copies!)
  std::cout << "Executing dumb swap: " << std::endl;
  auto t1 = std::clock(); // keep track of start time
  A tmp1 = data1;
  data1 = data2;
  data2 = tmp1;
  auto t2 = std::clock(); // keep track of end time
  std::cout << "Done" << std::endl;

  // Swap by move (no copies!)
  std::cout << "Executing smart swap: " << std::endl;
  auto t3 = std::clock(); // keep track of start time
  A tmp2 (std::move(data1));
  data1 = std::move( data2 );
  data2 = std::move( tmp2 ) ;
  auto t4 = std::clock(); // keep track of end time
  std::cout << "Done" << std::endl;  


  std::cout << "Dumb swap took " << 1000.0*( t2-t1 ) / CLOCKS_PER_SEC << " ms. Smart swap took " << 1000.0*(t4 - t3) / CLOCKS_PER_SEC << " ms." << std::endl;
  return 0;
}
