#include <iostream>
#include <vector>
#include <cmath>

template< typename T>
class poisson_mg {
public :
  
  typedef std::vector< std::vector<T> > matrix_type;
  
  poisson_mg( matrix_type const & rho_in, T iaccuracy = 0.001, int iL = 64, int in_smooth = 5) :
    accuracy_(iaccuracy), L_(iL), n_smooth_(in_smooth), rho_(rho_in)
  {
    init_matrix(psi_, L_+2, L_+2);
    init_matrix(psi_new_, L_+2, L_+2);
    init_matrix(rho_, L_+2, L_+2);

    h_ = 1. / static_cast<T>(L_ + 1);      // assume physical size in x and y = 1

    steps_ = 0;
  }

  void reset_psi(){
    for( unsigned int i = 0; i < psi_.size(); ++i )
      for ( unsigned int j = 0; j < psi_[i].size(); ++j ){
        psi_new_[i][j] = psi_[i][j]; 
      }
  }

  static void init_matrix( matrix_type & matrix, unsigned int N, unsigned int M) {
    matrix.resize( N );
    for ( auto i = matrix.begin(); i != matrix.end(); ++i ) {
      i->resize(M);
    }
  }


  void Gauss_Seidel(T h, matrix_type& u, const matrix_type& f)
  {
    int L = u.size() - 2;

    // use checkerboard updating
    for (int color = 0; color < 2; color++)
      for (int i = 1; i <= L; i++)
        for (int j = 1; j <= L; j++)
          if ((i + j) % 2 == color)
            u[i][j] = 0.25 * (u[i - 1][j] + u[i + 1][j] +
                      u[i][j - 1] + u[i][j + 1] +
                      h * h * f[i][j]);
  }

  
  void execute(){
    T error = 1e30;
    unsigned int nmax = 10;
    while ( error > accuracy_ && steps_ < nmax ){
      std::cout << "step " << steps_ << std::endl;
      two_grid(get_h(), get_psi(), get_rho());
      inc_steps();
      error = relative_error();
    }
  }

  void two_grid(T h, matrix_type& u, matrix_type& f)
  {
    std::cout << "make u" << std::endl;
    // solve exactly if there is only one interior point
    int L = u.size() - 2;
    if ( L == 0 )
      return;
    if (L == 1) {
      u[1][1] = 0.25 * (u[0][1] + u[2][1] + u[1][0] + u[1][2] +
                h * h * f[1][1]);
      return;
    }

    // do a few pre-smoothing Gauss-Seidel steps
    for (int i = 0; i < n_smooth_; i++)
      Gauss_Seidel(h, u, f);

    // find the residual
    matrix_type r;
    init_matrix(r, L+2, L+2);
    for (int i = 1; i <= L; i++)
      for (int j = 1; j <= L; j++)
        r[i][j] = f[i][j] +
          ( u[i + 1][j] + u[i - 1][j] +
            u[i][j + 1] + u[i][j - 1] - 4 * u[i][j]) / (h * h);

    // restrict residual to coarser grid
    int L2 = L / 2;
    matrix_type R;
    init_matrix(R, L2 + 2, L2 + 2);
    for (int I = 1; I <= L2; I++) {
      int i = 2 * I - 1;
      for (int J = 1; J <= L2; J++) {
        int j = 2 * J - 1;
        R[I][J] = 0.25 * ( r[i][j] + r[i + 1][j] + r[i][j + 1] +
                   r[i + 1][j + 1]);
      }
    }

    
    // initialize correction V on coarse grid to zero
    matrix_type V;
    init_matrix(V, L2 + 2, L2 + 2);

    // call twoGrid recursively
    T H = 2 * h;
    two_grid(H, V, R);

    // prolongate V to fine grid using simple injection
    matrix_type v;
    init_matrix(v, L + 2, L + 2);
    for (int I = 1; I <= L2; I++) {
      int i = 2 * I - 1;
      for (int J = 1; J <= L2; J++) {
        int j = 2 * J - 1;
        v[i][j] = v[i + 1][j] = v[i][j + 1] = v[i + 1][j + 1] = V[I][J];
      }
    }

    // correct u
    for (int i = 1; i <= L; i++)
      for (int j = 1; j <= L; j++)
        u[i][j] += v[i][j];

    // do a few post-smoothing Gauss-Seidel steps
    for (int i = 0; i < n_smooth_; i++)
      Gauss_Seidel(h, u, f);
  }

  T relative_error()
  {
    T error = 0;           // average relative error per lattice point
    int n = 0;                  // number of non-zero differences

    for (int i = 1; i <= L_; i++)
      for (int j = 1; j <= L_; j++) {
        if (psi_new_[i][j] != 0.0)
          if (psi_new_[i][j] != psi_[i][j]) {
            error += std::fabs(1 - psi_[i][j] / psi_new_[i][j]);
            ++n;
          }
      }
    if (n != 0)
      error /= n;

    return error;
  }

  matrix_type const & get_psi() const { return psi_; }
  matrix_type const & get_psi_new() const { return psi_new_; }
  matrix_type const & get_rho() const { return rho_; }


  matrix_type  & get_psi()  { return psi_; }
  matrix_type  & get_psi_new()  { return psi_new_; }
  matrix_type  & get_rho()  { return rho_; }

  void set_psi    ( int i, int j, T f) { psi_[i][j] = f; }
  void set_psi_new( int i, int j, T f) { psi_new_[i][j] = f; }
  void set_rho    ( int i, int j, T f) { rho_[i][j] = f; }

  T get_h () const { return h_;}
  unsigned int    get_steps() const { return steps_; }

  void inc_steps() { ++steps_;}
protected : 

  T accuracy_;        // desired relative accuracy in solution
  int L_;             // number of interior points in each dimension
  int n_smooth_;      // number of pre and post smoothing iterations

  matrix_type psi_,   // solution to be found
    psi_new_,         // approximate solution after 1 iteration
    rho_;             // given source function

  T h_;               // step size
  unsigned int steps_;// number of iteration steps


};
