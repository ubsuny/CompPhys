#include <cmath>
#include <vector>
#include <cassert> 

void least_squares(            // makes a linear least-squares fit
    const std::vector<double>& x,  // std::vector of x values - input
    const std::vector<double>& y,  // std::vector of y values - input
    double& a,                     // fitted intercept - output
    double& b,                     // fitted slope - output
    double& sigma,                 // estimated error bar in y
    double& sigma_a,               // estimated error in intercept - output
    double& sigma_b)               // estimated error in slope - output
{
    // determine the number of data points
    int n = x.size();

    assert (n > 2);

    // declare and initialize various sums to be computed
    double s_x = 0, s_y = 0, s_xx = 0, s_xy = 0;

    // compute the sums
    for (int i = 0; i < n; ++i) {
        s_x += x[i];
        s_y += y[i];
        s_xx += x[i] * x[i];
        s_xy += x[i] * y[i];
    }

    // evaluate least-squares fit forumlas
    double denom = n * s_xx - s_x * s_x;

    assert ( fabs(denom) > 0.000001);

    a = (s_xx * s_y - s_x * s_xy) / denom;
    b = (n * s_xy - s_x * s_y) / denom;

    // estimate the variance in the data set
    double sum = 0;
    for (int i = 0; i < n; ++i) {
        double y_of_x_i = a + b * x[i];
        double error = y[i] - y_of_x_i;
        sum += error * error;
    }
    assert ( sum >= 0.0);
    sigma = sqrt(sum / (n - 2));        // estimate of error bar in y

    // estimate errors in a and b
    assert ( sigma >= 0.0 );
    assert ( s_xx >= 0.0 );
    sigma_a = sqrt(sigma * sigma * s_xx / denom);
    sigma_b = sqrt(sigma * sigma * n / denom);
}
