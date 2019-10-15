#include <iostream>
#include <assert.h>
#include <iomanip>
#include <ios>
#include <math.h>
 
void root_print_header(const char *algorithm, double accuracy)
{
  std::cout << "\n ROOT FINDING using " << algorithm
	    << "\n Requested accuracy = " << accuracy
	    << "\n Step     Guess For Root          Step Size      "
	    << "     Function Value"
	    << "\n ----  --------------------  --------------------"
	    << "  --------------------"
	    << std::endl;
}
 
void root_print_step(int step, double x, double dx, double f_of_x)
{
    int w = std::cout.width();
    int p = std::cout.precision();
    std::ios::fmtflags f = std::cout.flags();
    std::cout.setf(std::ios::right, std::ios::adjustfield);
    std::cout << " " << std::setw(4) << step << "  ";
    std::cout.setf(std::ios::left, std::ios::adjustfield);
    std::cout << std::setprecision(14)
         << std::setw(20) << x << "  "
         << std::setw(20) << dx << "  "
         << std::setw(20) << f_of_x
         << std::endl;
    std::cout.width(w);
    std::cout.precision(p);
    std::cout.setf(f);
}

void root_max_steps(const char *algorithm, int max_steps)
{
  std::cerr << " " << algorithm << ": maximum number of steps "
	    << max_steps << " exceeded" << std::endl;
  exit(1);
}

double root_simple(
    double f(double),       // function whose root is to be found
    double x,               // initial guess
    double dx,              // suggested step, must be in direction of root
    double accuracy=1e-6,   // accuracy in dx and default
    int max_steps=1000,     // maximum number of steps to take
    bool root_debug=false)  // print debugging info
{
    double f0 = f(x);
    double fx = f0;
 
    int step = 0;
    int root_number_of_steps = step;
    if (root_debug) {
        root_print_header("Simple Search with Step Halving", accuracy);
        root_print_step(step, x, dx, fx);
    }
 
    while (fabs(dx) > accuracy && fx != 0) {
        x += dx;                // take a step
        fx = f(x);
        if ( f0 * fx < 0 ) {    // jumped past root
            x -= dx;            // backup
            dx /= 2;            // halve the step size
        }
        step += 1;
        root_number_of_steps = step;
        if (step > max_steps)
            root_max_steps("root_simple", max_steps);
        if (root_debug)
            root_print_step(step, x, dx, fx);
    }
 
    return x;
}

double root_bisection(
    double f(double),       // function whose root is to be found
    double x1,              // on one side of root
    double x2,              // on the other side of root
    double accuracy=1e-6,   // accuracy in dx and default
    int max_steps=1000,     // maximum number of steps to take
    bool root_debug=false)  // print debugging info
{
    double f1 = f(x1);
    double f2 = f(x2);
    if (f1 * f2 > 0.0) {
        std::cerr << " root_bisection: f(x1) * f(x2) > 0.0" << std::endl;
        exit(1);
    }
    double x_mid = (x1 + x2) / 2.0;
    double f_mid = f(x_mid);
    double dx = x2 - x1;
    int step = 0;
    int root_number_of_steps = step;
    if (root_debug) {
        root_print_header("Bisection Search", accuracy);
        root_print_step(step, x_mid, dx, f_mid);
    }
 
    while (fabs(dx) > accuracy) {
        if (f_mid == 0.0)
            dx = 0.0;
        else {
            if (f1 * f_mid > 0) {
                x1 = x_mid;
                f1 = f_mid;
            } else {
                x2 = x_mid;
                f2 = f_mid;
            }
            x_mid = (x1 + x2) / 2.0;
            f_mid = f(x_mid);
            dx = x2 - x1;
        }
        step += 1;
        root_number_of_steps = step;
        if (step > max_steps)
            root_max_steps("root_bisection", max_steps);
        if (root_debug)
            root_print_step(step, x_mid, dx, f_mid);
    }
 
    return x_mid;
}




double root_secant(         // returns root of f(x)
    double f(double),       // function whose root is to be found
    double x0,              // first guess
    double x1,              // second guess
    double accuracy=1e-6,   // accuracy in dx and default
    int max_steps=20,       // maximum number of steps to take
    bool root_debug=false)  // debug info
{
    double f0 = f(x0);
    double dx = x1 - x0;
    int step = 0;
    if (root_debug) {
        root_print_header("Secant Search", accuracy);
        root_print_step(step, x0, dx, f0);
    }
    if (f0 == 0.0)
        return x0;
    while (abs(dx) > abs(accuracy)) {
        double f1 = f(x1);
        if (f1 == 0.0)
            return x1;
        if (f1 == f0) {
	  std::cerr << " Secant horizontal f(x0) = f(x1) algorithm fails"
		    << std::endl;
            exit(1);
        }
        dx *= - f1 / (f1 - f0);
        x0 = x1;
        f0 = f1;
        x1 += dx;
        step += 1;
        if (step > max_steps)
            root_max_steps("root_secant", max_steps);
        if (root_debug)
            root_print_step(step, x1, dx, f1);
    }

    return x1;
}

double root_tangent(        // returns root of f(x)
    double f(double),       // function whose root is to be found
    double fp(double),      // derivative df(x)/dx
    double x0,              // guess for root
    double accuracy=1e-6,   // accuracy in dx and default
    int max_steps=20,       // maximum number of steps to take
    bool root_debug=false)  // print debug info
{
    double f0 = f(x0);
    int step = 0;
    double fp0 = fp(x0);
    if (fp0 == 0.0) {
      std::cerr << " root_tangent df/dx = 0 algorithm fails"
		<< std::endl;
        exit(1);
    }
    double dx = - f0 / fp0;
    if (root_debug) {
        root_print_header("Tangent Search", accuracy);
        root_print_step(step, x0, dx, f0);
    }
    if (f0 == 0.0)
        return x0;
    while (true) {
        double fp0 = fp(x0);
        if (fp0 == 0.0) {
	  std::cerr << " root_tangent df/dx = 0 algorithm fails"
		    << std::endl;
            exit(1);
        }
        dx = - f0 / fp0;
        x0 += dx;
        f0 = f(x0);
        if (abs(dx) <= accuracy || f0 == 0.0)
            return x0;
        step += 1;
        if (step > max_steps)
            root_max_steps("root_tangent", max_steps);
        if (root_debug)
            root_print_step(step, x0, dx, f0);
    }

    return x0;
}
