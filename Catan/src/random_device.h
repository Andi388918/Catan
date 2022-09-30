#pragma once

#include <random>

class RandomDevice
{
public:
	int next();

private:
	std::default_random_engine ran;
};