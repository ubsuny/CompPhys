#include <iostream>
#include <fstream>
#include <sstream>

int main() {

  std::ifstream inputfile("../ClassExample/points.txt");

  // Loop over lines in file
  std::string line; // Storage for the current line
  while (std::getline(inputfile, line)) { // At the end of the file, std::getline() will evaluate to false, ending the loop
    std::cout << "Read line: " << line << std::endl;
  }
  std::cout << std::endl;
  inputfile.close();

  // More complicated example: 
  // Each line contains two numbers and a comma: "x,y"
  // Let's extract x and y, and read into floats.
  // We can reuse std::getline(), telling it to split on ',' rather than '\n'
  inputfile.open("points.txt");
  while (std::getline(inputfile, line)) { 
    std::stringstream line_stream(line); // std::getline() expects a stream, not just a string. We can use the std::stringstream class for this.
    std::string x_str;
    std::getline(line_stream, x_str, ',');
    float x = std::atof(x_str.c_str());

    std::string y_str;
    std::getline(line_stream, y_str, ',');
    float y = std::atof(y_str.c_str());

    std::cout << "(x, y) = (" << x << ", " << y << ")" << std::endl;
  }
}
