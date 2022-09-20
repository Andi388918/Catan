
#pragma once

#include <exception>
#include <vector>

#include "coords.h"

static const std::vector<Coords> intersection_offsets = {
	Coords{1, 0},
	Coords{0, 1},
	Coords{-1, 1},
	Coords{-1, 0},
	Coords{0, -1},
	Coords{1, -1}
};

struct Hex
{
	class InvalidHexNumber : public std::exception {};
	enum class Type { brick, lumber, wool, grain, ore, desert, lake, random, invalid };

	Type type;
	Coords coords;
	std::vector<int> numbers;

	Hex() {}
	Hex(Type type, std::vector<int> numbers = {});
};