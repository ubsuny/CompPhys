#ifndef metropolis_h
#define metropolis_h

#include <string>
#include <cmath>
#include <random>
#include <iostream>
#include <fstream> 

template< typename P, typename T >
class metropolis {

public : 

  metropolis(P const & p, T iwalker, T idelta, int inskip, bool iv) :
    probdist(p), 
    rd(), gen(rd()), dis(-1.,1.),
    x_walker(iwalker), delta(idelta), nskip(inskip),
    steps(0), accepts(0),verbose(iv)
  {
    if(verbose) debug.open("debug.txt");
  }

  ~metropolis(){
    debug.close();
  }
  
  bool metropolis_step()              // return true if step accepted, else false
  {
    auto a1 = dis(gen);         // need this from -1 --> 1
    auto x_trial = x_walker + delta*a1;
    auto g1 = probdist(x_trial);
    auto g2 = probdist(x_walker);
    auto ratio = g1 / g2;
    auto a2 = (dis(gen)+1)*0.5; // need this between 0-->1
    if(verbose){
        char buff[1000];
        sprintf( buff, " (%6.2f, %6.2f) --> (%6.2f, %6.2f), ratio = %6.2f, a1= %6.2f, a2 = %6.2f ", x_walker, g2, x_trial, g1, ratio, a1, a2);
        debug << buff << std::endl;
    } 
    if (a2 < ratio) {
      x_walker = x_trial;
      return true;
    } else {
      return false;
    }
  }

  void monte_carlo_step()
  {
    for (unsigned int i = 0; i < nskip; ++i)
      metropolis_step();
    if (metropolis_step())
      ++accepts;
    ++steps;
  }

  T get() const { return x_walker; }
    
  P get_probdist() const { return probdist;}

protected :

  P probdist;                           // Probability distribution class (template parameter)

  // C++11 random number generator from Mersenne twister. 
  std::random_device rd;
  std::mt19937 gen;
  std::uniform_real_distribution<> dis;
  
  // Metropolis
  T x_walker;               // current position
  T delta;                  // step size

  unsigned long nskip;       // steps to skip for thermalization
  unsigned long steps;       // steps so far
  unsigned long accepts;     // steps accepted

  std::ofstream debug;
  bool verbose; 
};

#endif
