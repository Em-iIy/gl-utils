#pragma once

#include <random>

namespace rng
{

	void	seed();

	typedef std::uniform_real_distribution<float> fgen;
	fgen	generator(const float f1, const float f2);

	float	rand(fgen &gen);

	typedef std::uniform_int_distribution<int> igen;
	igen		generator(const int n1, const int n2);

	int	rand(igen &gen);
}