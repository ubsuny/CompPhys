#include "reptation.h"
using namespace std;

bool Reptation::occupied(Site s) {     // return true if s is occupied
    return occupiedSites.find(s) != occupiedSites.end();
}

void Reptation::clear() {              // remove all sites
    snake.clear();
    occupiedSites.clear();
}

void Reptation::addBack(Site s) {      // add s to back of reptile
    snake.push_back(s);
    occupiedSites.insert(s);
}

void Reptation::addFront(Site s) {     // add s to back of reptile
    snake.push_front(s);
    occupiedSites.insert(s);
}

void Reptation::removeBack() {         // remove back end of reptile
    occupiedSites.erase(snake.back());
    snake.pop_back();
}

void Reptation::removeFront() {        // remove front end of reptile
    occupiedSites.erase(snake.front());
    snake.pop_front();
}

void Reptation::createSnake(           // make a snake with
    int steps,              // this number of segments
    int config)             // and this initial configuration
{
    clear();                // remove all sites

    Site s;
    s.x = s.y = 0;
    addFront(s);

    for (int step = 1; step <= steps; step++) {

      int stp = 0, dir = EAST;    // initialize variables to construct coil

      switch (config) {
      case STAIR:             // add randomly East or North
	dis(gen) < 0.5 ? ++s.x : ++s.y;  // distribution chooses 0,1,2,3
	break;
      case COIL:              // add in sequence E,N,W,W,S,S,E,E,E,N,N,N,...
	while (stp < step)
	  stp += ++dir / 2;
	switch ((dir + 2) % DIRECTIONS) {
	case EAST  :  ++s.x;  break;
	case NORTH :  ++s.y;  break;
	case WEST  :  --s.x;  break;
	case SOUTH :  --s.y;  break;
	}
	break;
      case LINE:              // add East
      default:                // also the default
	++s.x;
      }
	
      addFront(s);
    }
}

Site Reptation::randomAllowed(         // return a random allowed site
    Site head,              // adjacent to this head site
    Site neck)              // excluding this neck site
{
    deque<Site> allowed;

    // find the 3 allowed directions and add site to allowed deque

    for (int direction = EAST; direction < DIRECTIONS; direction++) {

        Site s;
        s.x = head.x;
        s.y = head.y;

        switch (direction) {
        case EAST:
            if ( !(head.x == neck.x - 1 && head.y == neck.y) ) {
                ++s.x;
                allowed.push_back(s);
            }
            break;
        case NORTH:
            if ( !(head.x == neck.x && head.y == neck.y - 1) ) {
                ++s.y;
                allowed.push_back(s);
            }
            break;
        case WEST:
            if ( !(head.x == neck.x + 1 && head.y == neck.y) ) {
                --s.x;
                allowed.push_back(s);
            }
            break;
        case SOUTH:
            if ( !(head.x == neck.x && head.y == neck.y + 1) ) {
                --s.y;
                allowed.push_back(s);
            }
            break;
        }
    }

    // choose and return a random allowed site
    return allowed[ static_cast<int>(dis(gen) * allowed.size()) ];
}

bool Reptation::reptate() {            // attempt random move and return true if succeeded

    if (snake.size() < 2)               // cannot reptate
        return false;

    Site head, neck, sNext;

    if (dis(gen) < 0.5 ) {    // choose front end of snake
        head = snake[0];
        neck = snake[1];
        sNext = randomAllowed(head, neck);
        if (occupied(sNext))
            return false;
        removeBack();
        addFront(sNext);
    } else {                            // choose back end of snake
        int n = snake.size();
        head = snake[n - 1];
        neck = snake[n - 2];
        sNext = randomAllowed(head, neck);
        if (occupied(sNext))
            return false;
        removeFront();
        addBack(sNext);
    }

    return true;
}

double Reptation::rSquared() {         // end-to-end size squared
    if (snake.size() < 2)
        return 0.0;
    double dx = snake.front().x - snake.back().x;
    double dy = snake.front().y - snake.back().y;
    return dx * dx + dy * dy;
}

void Reptation::run(){
  for (int steps = 1; steps <= n_steps; steps++) {
    double r2sum = 0;
    double r4sum = 0;
    int success = 0;
    createSnake(steps, config);
    for (int i = 0; i < n_walks; i++) {
      if (reptate())
	++success;
      double r2 = rSquared();
      r2sum += r2;
      r4sum += r2 * r2;
      
      if ( makePlot ) {
	snakes.push_back( snake );
      }
    }
    r2av.push_back( r2sum / n_walks );
    stdDev.push_back( sqrt(r4sum / n_walks - r2av.back() * r2av.back()) );
    successPercent.push_back( success / double(n_walks) );

  }
}
