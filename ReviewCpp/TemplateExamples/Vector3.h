#ifndef Vector3_h
#define Vector3_h

#include <cmath>
#include <iostream>

template<class T>
class Vector3 {
public:
	// Vector3(double ix=0., double iy=0., double iz=0.) {...}
	~Vector3() {}


	// "Getter" functions. x is provided for you; write the same functions for y and z.
	//T x() const {
	//	return x_;
	//}


	// "Setter" functions. x is provided for you; write the same functions for y and z.
	//Vector3<T>& set_x(T ix) {
	//	x_ = ix;
	//	return *this;
	//}


	// Write a function that returns the length of the vector (sqrt(x^2 + y^2 + z^2)). 
	// Use the pow(x, y) function to compute x^y.
	// The function is const, because it only returns info about Vector3, it does not modify it.
	// T length() const {...}

	// Print function
	void print() const {
		std::cout << x_ << ", " << y_ << ", " << z_ << std::endl;
	}

	// Addition operator
	Vector3<T> operator + (Vector3 const& right) const {
		Vector3 retval(x_ + right.x(), y_ + right.y(), z_ + right.z());
		return retval;
	}

	// Member data (private)
private:
	// x is provided for you. Write the same for y and z
	// T x_; 
};

// "Explicit instantiation": this tells the compiler to create an actual class from the template, 
// with T=double.
template class Vector3<double>;

#endif