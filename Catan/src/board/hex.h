
#pragma once

#include <exception>
#include <vector>

#include "Coordinates.h"

static const std::vector<Coordinates> intersection_offsets = {
	Coordinates {1, 0},
	Coordinates {0, 1},
	Coordinates {-1, 1},
	Coordinates {-1, 0},
	Coordinates {0, -1},
	Coordinates {1, -1}
};

class Hex
{
public:
	class InvalidHexNumber : public std::exception {};
	enum class Type { Brick, Lumber, Wool, Grain, Ore, Desert, Lake, Random, Undefined };

	Hex(Type type = Type::Undefined, std::vector<int> numbers = {});

	bool is_undefined() const { return type == Type::Undefined; }
	Type get_type() const { return type; }
	std::vector<int> get_numbers() const { return numbers; }

private:
	Type type;
	std::vector<int> numbers;
};