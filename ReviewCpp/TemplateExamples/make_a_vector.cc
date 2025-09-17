#include "Vector3.h"
#include <iostream>

int main() {
	std::cout << "Making some vectors" << std::endl;
	Vector3<double> v1(3, 4, 5.);
	v1.print();

	Vector3<double> v2(12, 35, 37);
	v2.print();

	Vector3<double> v3(68, 285, 293);
	v3.print();

	(v1 + v2).print();


	// Make a vector Vector3s
	std::vector<Vector3<double>> vlist;
	vlist.push_back(v1);
	vlist.push_back(v3);
	vlist.push_back(v2);

	// Print out the elements in order
	std::cout << std::endl << "Printing vlist:" << std::endl;
	for (auto& it : vlist) {
		it.print();
	}

	// Sort the vector 
	std::sort(vlist.begin(), 
		vlist.end(), 
		[](const Vector3<double>& left, const Vector3<double>& right) { return left.length() < right.length(); }
	);

	// Print out the elements again, they should be sorted
	std::cout << std::endl << "Printing vlist again after sorting by length:" << std::endl;
	for (auto& it : vlist) {
		it.print();
	}


}