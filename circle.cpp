#include "circle.h"
#include <sstream>
#include <limits.h>


circle::circle(double rad) {
	if (rad <= 0 || !std::isfinite(rad)) {
		throw std::invalid_argument("Invalid input");
	}
	this->rad = rad;
	double p = PI * 2.0 * rad;
	if (!std::isfinite(p)) {
		throw std::overflow_error("Circle Perimeter overflow");
	}
	
}
double circle::perimeter() const{
	return PI * 2.0 * rad;
}
std::string circle::to_string() const {
	std::stringstream s;
	s << "circle " << rad;
	return s.str();
}