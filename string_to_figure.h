#pragma once
#include "figures.h"
#include "circle.h"
#include "triangle.h"
class string_to_figure {
public:
	figure* create_from(std::string representation) const ;
};
