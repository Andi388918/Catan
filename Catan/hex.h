
#pragma once

#include <exception>
#include <vector>
#include <algorithm>
#include <array>

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

	bool is_random() const { return type == Type::random; }
	std::array<Coords, 6> intersections() const;

	Coords get_coords() const { return coords; }

private:
	Type type;
	Coords coords;
	std::vector<int> numbers;
};