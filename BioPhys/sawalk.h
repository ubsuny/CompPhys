#ifndef SAWALK_H
#define SAWALK_H

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <random>

struct Site {               // object to represent lattice site
    int x;                  // x coordinate
    int y;                  // y coordinate
};

class SAWalk{

public: 
  SAWalk(unsigned int n_steps_in, unsigned int n_walks_in):  
  rd(), gen(rd()), dis(0,4),
  n_steps(n_steps_in), n_walks(n_walks_in),walks(0),failed_walks(0),r2av(0.), r4av(0.), stdDev(0.) {
  };

  void run();

  unsigned int get_nsteps() const { return n_steps; }
  unsigned int get_nwalks() const { return n_walks; }
  int get_walks() const { return walks; }
  int get_failed_walks() const {return failed_walks; }
  double get_r2av() const {return r2av; }
  double get_r4av() const {return r4av; }
  double get_stdDev() const {return stdDev;}

protected:
  std::random_device rd;
  std::mt19937 gen;
  std::uniform_int_distribution<> dis;
  
  unsigned int n_steps, n_walks;
  int walks;
  int failed_walks;
  double r2av;
  double r4av;
  double stdDev; 
  std::vector<Site> sites;
};


#endif
