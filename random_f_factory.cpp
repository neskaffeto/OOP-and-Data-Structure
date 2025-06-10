#include "random_f_factory.h"

figure* stream_figure_factory::create() {
	
	std::string line;
	std::getline(in, line);
	if (line.empty()) {
		throw std::invalid_argument("Empty stream");
	}
	return parse.create_from(line);
}

void random_figure_factory::ensure_seed() {
	if (!seeded) {
		std::srand(static_cast<unsigned int>(std::time(nullptr)));
		seeded = true;
	}
}

double random_figure_factory::random_double(double min, double max) {
	ensure_seed();
	double scale = rand() / (double)RAND_MAX;
	return min + scale * (max - min);
}

figure* random_figure_factory::create() {
	ensure_seed();
	int shape = rand() % 2; //ako se dobavqt oshte figuri uvelichavame chisloto
	//0 = circle , 1 = triangle
	if(shape == 0) {
		double r = random_double(DBL_MIN, DBL_MAX);
		while (r <= 0 || !std::isfinite(r)) {
			double r = random_double(DBL_MIN, DBL_MAX);
		}
		return new circle(r);
	}
	else if (shape == 1) {
		double a, b, c;
		do {
			a= random_double(1, 100);
			b = random_double(1, 100);
			c= random_double(1, 100);
		} while (a + b <= c || a + c <= b || b + c <= a);
		return new triangle(a, b, c);
	}
}
