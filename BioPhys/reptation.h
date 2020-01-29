#ifndef reptation_h
#define reptation_h

#include <cmath>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <deque>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <set>
#include <random>


struct Site {               // object to represent lattice site
    int x;                  // x coordinate
    int y;                  // y coordinate

    // strict weak-ordering comparison operator required by set
    bool operator< (const Site& s) const {
        const int maxDiff = 9999;   // must be larger than x or y difference
        return (x - s.x) + maxDiff * (y - s.y) < 0;
    }
};

class Reptation{

public:
  enum { EAST = 0, NORTH, WEST, SOUTH, DIRECTIONS};
  enum { STAIR = 0, COIL, LINE };


  
  Reptation(int n_steps_in, int n_walks_in, int config_in, bool plot=false) :
    rd(), gen(rd()), dis(0,1),
    n_steps(n_steps_in), n_walks(n_walks_in), config(config_in), makePlot(plot)
  {
  }

  bool occupied(Site s);     // return true if s is occupied
  void clear();              // remove all sites
  void addBack(Site s);      // add s to back of reptile=
  void addFront(Site s);    // add s to back of reptile
  void removeBack();        // remove back end of reptile
  void removeFront();         // remove front end of reptile



  void createSnake(           // make a snake with
		   int steps,              // this number of segments
		   int config = LINE);     // and this initial configuration

  Site randomAllowed(         // return a random allowed site
		     Site head,              // adjacent to this head site
		     Site neck);             // excluding this neck site;
  bool reptate() ;
  double rSquared();

  
  void run(); 
  std::vector<double> const & get_r2av() const { return r2av; }
  std::vector<double> const & get_stdDev() const { return stdDev; }
  std::vector<double> const & get_successPercent() const { return successPercent; }

  std::vector< std::deque<Site> > const & get_snakes() const { return snakes; }
  
protected:

  std::random_device rd;
  std::mt19937 gen;
  std::uniform_real_distribution<> dis;

  std::deque<Site> snake;          // double-headed reptile
  std::set<Site> occupiedSites;    // set of occupied sites
  std::vector< std::deque<Site> > snakes; // Here we keep track of the sites for plotting
  
  int n_steps, n_walks, config;
  bool makePlot;                   // store a list of the snakes
  int walks;
  int failed_walks;
  std::vector<double> r2av;
  std::vector<double> stdDev;
  std::vector<double> successPercent;


};

#endif
