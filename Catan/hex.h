
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

class Hex
{
public:
	class InvalidHexNumber : public std::exception {};
	enum class Type { Brick, Lumber, Wool, Grain, Ore, Desert, Lake, Random, Invalid };

	Hex() : type { Type::Invalid } {}
	Hex(Type type, std::vector<int> numbers = {});

	bool is_random() { return type == Type::Random; }

private:
	Type type;
	std::vector<int> numbers;
};