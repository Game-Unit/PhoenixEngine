#include "Random.h"

#include <random>

int Core::Random::Range(int min, int max)
{
    std::random_device rd;

    std::mt19937 gen(rd());

    std::uniform_int_distribution<> distrib(min, max);

	return distrib(gen);
}
