#pragma once
#include <string>

class string_convertible {
public:
	virtual std::string to_string() const = 0;
	virtual ~string_convertible() = default;
};