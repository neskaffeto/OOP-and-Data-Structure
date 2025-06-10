#include "string_to_figure.h"
#include <sstream>
figure* string_to_figure::create_from(std::string representation) const {
	std::istringstream input(representation);
	std::string str;
	input >> str;
	if (!input || str.empty()) {
		throw std::invalid_argument("Empty input");
	}
	if (str == "circle") {
		double r;
		input >> r;
		if (!input) {
			throw std::invalid_argument("Invalid radius");
		}
		return new circle(r);
	}
	else if (str == "triangle") {
		double a, b, c;
		input >> a >> b >> c;
		if (!input) {
			throw std::invalid_argument("Invalid triangle sides");
		}
		return new triangle(a, b, c);
	}
	else {
		throw std::invalid_argument("Unknown shape" + str);
	}
}