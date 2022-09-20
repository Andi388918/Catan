
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
	enum class Type { brick, lumber, wool, grain, ore, desert, lake, random, invalid };

	Hex(Type type, Coords coords, std::vector<int> numbers = {});

	/* accessors */

	bool is_random() const { return type == Type::random; }
	Coords get_coords() const { return coords; }
	std::vector<int> get_numbers() const { return numbers; }

private:
	Type type;
	Coords coords;
	std::vector<int> numbers;
};