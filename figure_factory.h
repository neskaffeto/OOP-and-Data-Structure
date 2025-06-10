#pragma once
#include "figures.h"

class figure_factory {
public:
	virtual figure* create() = 0;
	virtual ~figure_factory() = default;
};
