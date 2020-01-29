#include "SAWalk.h"


void SAWalk::run() {


  walks = 0;
  failed_walks = 0;
  r2av = 0;
  r4av = 0;
  stdDev = 0;

  // generate walks
  while (walks < n_walks) {
    sites.clear();  // set of occupied lattice sites
    Site s;
    s.x = 0;
    s.y = 0;
    sites.push_back(s);
    bool walk_failed = false;

    // loop over desired number of steps
    for (int step = 0; step < n_steps; step++) {

      // take a random step
      auto dir = dis(gen);
      if      (dir == 0)  ++s.x;   // step East
      else if (dir == 1)  ++s.y;   // step North
      else if (dir == 2)  --s.x;   // step West
      else                --s.y;   // step South

      // check whether the site is occupied
      bool occupied = false;
      for (int i = 0; i < sites.size(); i++) {
	if (s.x == sites[i].x && s.y == sites[i].y) {
	  occupied = true;
	  break;
	}
      }
      if (occupied) {
	walk_failed = true;
	break;
      }

      sites.push_back(s);
    }

    if (walk_failed) {
      ++failed_walks;
      continue;
    }

    double r2 = s.x * s.x + s.y * s.y;
    r2av += r2;
    r4av += r2 * r2;
    ++walks;
  }

  r2av /= n_walks;
  r4av /= n_walks;
  stdDev = sqrt(r4av - r2av * r2av);
}
