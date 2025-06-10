#pragma once
#include <stdexcept>
#include "stringto.h"
class figure: public string_convertible {
public:
	virtual double perimeter() const=0;
	virtual ~figure() = default;
};