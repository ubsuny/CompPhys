#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "Point.h"

int main(void) {

    // Create input file stream
    std::ifstream inputfile("points.txt");

    // Make a vector for storing points
    std::vector<Point> points_vec;

    // Loop over lines in file
    // We use std::getline(), which reads the next line from inputfile into our string current_line
    // Note: a "line" is defined by reading characters one at a time from the stream, 
    //    until a newline (\n) is reached.
    // At end of file, std::getline() return False, ending the while(){} loop
    std::string current_line;
    while (std::getline(inputfile, current_line)) { 
        std::cout << "current_line = " << current_line << std::endl;

        // Each line contains a pair of numbers, like "1,2"
        // To parse the line, we will (ab)use std::getline again.
        // Instead of reading characters until a newline (\n), we can tell std::getline to break on a comma.
        std::stringstream line_stream(current_line); // std::getline() expects a stream, not just a string. We can use the std::stringstream class for this.
        std::string x_str;
        std::getline(line_stream, x_str, ',');
        float x = std::atof(x_str.c_str()); // std::atof turns a string into a float

        std::string y_str;
        std::getline(line_stream, y_str, ',');
        float y = std::atof(y_str.c_str());

        Point point = Point(x, y);
        std::cout << "Created point: " << std::endl;
        point.print();

        // Store the point in the vector
        points_vec.push_back(point);

        std::cout << std::endl;
    }

    // Test the vector
    std::cout << "Testing the vector" << std::endl;
    for (auto& it_point : points_vec) {
        it_point.print();
    }

    inputfile.close();


}
