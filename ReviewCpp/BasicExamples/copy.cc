#include <iostream>

struct C {
  C() { std::cout << "Constructor called" << std::endl;}
  C(const C&) { std::cout << "A copy was made" << std::endl; }
};

C f() {
  C ret = C();
  return ret;
}

int main() {
  std::cout << "Hello World!\n";
  std::cout << "Testing direct creation" << std::endl;
  C direct_obj = C();
  std::cout << "Testing functional creation" << std::endl;
  C obj = f();
}
