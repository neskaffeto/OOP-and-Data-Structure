#pragma once
#include "figure_factory.h"
#include "string_to_figure.h"

#include <random>
#include <iostream>
#include <sstream>

class stream_figure_factory : public figure_factory{
private:
	std::istream& in;
	string_to_figure parse;
public:
	stream_figure_factory(std::istream& in): in(in) {}
	figure* create() override;
};

class random_figure_factory : public figure_factory {
	bool seeded = false;
	void ensure_seed();
	double random_double(double min, double max);
public:
	figure* create() override;
};