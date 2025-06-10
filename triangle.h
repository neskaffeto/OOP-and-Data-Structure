#pragma once
#include "figures.h"
class triangle :public figure {
	double a, b, c; //3-te strani na triugulnika
public:
	triangle(double a, double b, double c);
	double perimeter() const override;
	std::string to_string() const override;
};