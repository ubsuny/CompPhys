#include <iostream>
#include <vector>
#include <random>
#include <chrono>



// This is a program to demonstrate the various vectorization optimizations
// that can be used with g++. It is expected to be profiled with
// various compiler optimization settings:
// No optimization: g++ vectorization.cpp -std=c++11 -o vectorization -O0
// Vectorization at compile time: g++ vectorization.cpp -std=c++11 -o vectorization -O1
// Vectorization at run time: g++ vectorization.cpp -std=c++11 -o vectorization -O2

int main(int argc, char ** argv)
{
  using namespace std;
  using namespace std::chrono;

  
  if ( argc < 2) {
    cout << "Enter N." << endl;
    return 0;
  }


  // Initialize a random number generator.
  random_device rd{};
  mt19937 gen(rd());
  uniform_real_distribution<double> dis(0.0, 1.0);


  // First, let's check the case where the compiler knows
  // nothing about the size of the vector so can perform only
  // limited optimizations. 

  // Create three vectors, initialize the first two to random deviates. 
  int N = atoi(argv[1]);
  vector<double> A, B, C;
  A.resize(N);
  B.resize(N);
  C.resize(N);
  for ( unsigned int i = 0; i < N; ++i ){
    A[i] = dis(gen);
    B[i] = dis(gen);
  }

  // Measure the time of the loop and print it.
  auto t1 = high_resolution_clock::now();
  for ( unsigned int i = 0; i < N; ++i ) {
    C[i] = A[i] + B[i];
  }  
  auto t2 = high_resolution_clock::now();   
  auto duration = duration_cast<microseconds>( t2 - t1 ).count();
  cout << "Vector, unknown size = " << duration << " us" << endl;

  // Next, let's check the case where we have a static const
  // size, so the compiler knows the size of the vector and can
  // possibly optimize.

  // Initialize again
  static const int M = 100000;
  vector<double> vA(M),vB(M),vC(M);
  for ( unsigned int i = 0; i < N; ++i ){
    vA[i] = dis(gen);
    vB[i] = dis(gen);
  }

  // Time and print
  t1 = high_resolution_clock::now();
  for ( unsigned int i = 0; i < N; ++i ) {
    vC[i] = vA[i] + vB[i];
  } 
  t2 = high_resolution_clock::now();  
  duration = duration_cast<microseconds>( t2 - t1 ).count();
  cout << "Vector, known size = " << duration << " us" << endl;


  // Finally, let's look at the case of an array instead of a
  // vector. This gets allocated on the memory stack, and not the memory heap.
  // The compiler can optimize this very strongly. 


  // Initialize
  double aA[M], aB[M], aC[M];
  for ( unsigned int i = 0; i < N; ++i ){
    aA[i] = dis(gen);
    aB[i] = dis(gen);
  }

  // Time and print. 
  t1 = high_resolution_clock::now();
  for ( unsigned int i = 0; i < N; ++i ) {
    aC[i] = aA[i] + aB[i];
  }  
  t2 = high_resolution_clock::now();   
  duration = duration_cast<microseconds>( t2 - t1 ).count();
  cout << "Static array = " << duration << " us" << endl;


  // Now try to unroll by hand
  // Time and print. 
  t1 = high_resolution_clock::now();
  double aD[M];
  for ( unsigned int i = 0; i < N; i += 5 ) {
    aC[i+0] = aA[i+0] + aB[i+0];
    aC[i+1] = aA[i+1] + aB[i+1];
    aC[i+2] = aA[i+2] + aB[i+2];
    aC[i+3] = aA[i+3] + aB[i+3];
    aC[i+4] = aA[i+4] + aB[i+4];
  }  
  t2 = high_resolution_clock::now();   
  duration = duration_cast<microseconds>( t2 - t1 ).count();
  cout << "Static array, unroll by hand : Duration = " << duration << " us" << endl;

  

  // Compiler is clever and optimizes away the computation if we don't
  // actually use it somewhere, so print out the values.


  cout << C[0] << endl;
  cout << aC[0] << endl;
  cout << vC[0] << endl;
  cout << aD[0] << endl;  
  return 0;
}
