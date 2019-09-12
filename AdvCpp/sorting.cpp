#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>

class A{
public:
  A(){}
  A(std::string n, double s) : name_(n), score_(s) {}

  inline std::string name() const {return name_;}
  inline double score() const {return score_;}

  bool operator<( A const & right ) const {
    return score_ < right.score_; 
  }

  friend std::ostream & operator<<( std::ostream & out, const A & a) {
    out << a.name_ << ", " << a.score_;
    return out; 
  }
protected:
  std::string name_; 
  double score_;
};

int main(void)
{

  std::vector<std::string> names = {"Sonny", "Michael", "Fredo"}; // You broke my heart, Fredo. 
  std::vector<double> scores = {85., 95., 15.}; 
  std::vector<A> values(names.size());

  
  std::cout << "Before sorting: " << std::endl;
  for ( auto ibegin = values.begin(), iend = values.end(), i = values.begin(); i != iend; ++i ) {
    *i = A(names[i-ibegin],scores[i-ibegin]);
    std::cout << *i << std::endl;
  }
  
  std::sort( values.begin(), values.end() );

  std::cout << "After sorting: " << std::endl;
  for ( auto ibegin = values.begin(), iend = values.end(), i = values.begin(); i != iend; ++i ) {
    std::cout << *i << std::endl;
  }

  return 0;
  
}
