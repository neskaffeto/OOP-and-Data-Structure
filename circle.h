#pragma once
#include "figures.h"
constexpr double PI = 3.14159265358979323846;
class circle :public figure {
	double rad; //radius
public:
	circle(double rad);
	double perimeter() const override;
	std::string to_string() const override;
};