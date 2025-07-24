#include <random>

#include "rng.hpp"

namespace rng
{
	static std::mt19937			mt;

	void	seed()
	{
		std::random_device	rd;
		mt = std::mt19937(rd());
	}

	fgen	generator(const float f1, const float f2)
	{
		return (fgen(f1, f2));
	}
	
	float	rand(fgen &gen)
	{
		return (gen(mt));
	}
	
	igen	generator(const int n1, const int n2)
	{
		return (igen(n1, n2));
	}
	
	int	rand(igen &gen)
	{
		return (gen(mt));
	}
}