#include "triangle.h"
#include <sstream>
triangle::triangle(double a, double b, double c) {
	if (a <= 0 || b <= 0 || c <= 0 || !std::isfinite(a) || !std::isfinite(b) || !std::isfinite(c)) {
		throw std::invalid_argument("Invalid input");
	}           
	if (a + b <= c || a + c <= b || b + c <= a) {
		throw std::invalid_argument("Impossible triangle");
	}
	this->a = a;
	this->b = b;
	this->c = c;
	double p = a + b + c;
	if (!std::isfinite(p)) {
		throw std::overflow_error("Triangle perimeter is not finite");
	}
}

double triangle::perimeter() const {
	return a + b + c;
}

std::string triangle::to_string() const {
	std::stringstream s;
	s << "triangle " << a << " " << b << " " << c;
	return s.str();
}