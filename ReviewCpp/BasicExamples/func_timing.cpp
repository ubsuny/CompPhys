#include <iostream>
#include <chrono>
#include <vector>


void print_val(std::vector<double> vec) {
  std::cout << "vec.size() = " << vec.size() << std::endl;
}

void print_ptr(std::vector<double> * vec) {
  std::cout << "vec->size() = " << vec->size() << std::endl;
}

void print_ref(std::vector<double> & vec) {
  std::cout << "vec.size() = " << vec.size() << std::endl;
}

int main(void){
  using std::chrono::high_resolution_clock;
  using std::chrono::duration_cast;
  using std::chrono::duration;
  using std::chrono::milliseconds;

  std::vector<double> vec;
  for (int i = 0; i < 100000000; ++i) {
    vec.push_back(i);
  }

  // Test pass by value
  std::cout << "Pass by value" << std::endl;
  auto t1 = high_resolution_clock::now();
  print_val(vec);
  auto t2 = high_resolution_clock::now();
  std::cout << "Time: " << duration<double, std::milli>(t2 - t1).count() << " ms" << std::endl;

  // Test pass by pointer
  std::cout << "Pass by pointer" << std::endl;
  auto t3 = high_resolution_clock::now();
  print_ptr(&vec);
  auto t4 = high_resolution_clock::now();
  std::cout << "Time: " << duration<double, std::milli>(t4 - t3).count() << " ms" << std::endl;

  // Test pass by value
  std::cout << "Pass by reference" << std::endl;
  auto t5 = high_resolution_clock::now();
  print_ref(vec);
  auto t6 = high_resolution_clock::now();
  std::cout << "Time: " << duration<double, std::milli>(t6 - t5).count() << " ms" << std::endl;

  
  return 0;
}
