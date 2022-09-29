
#pragma once

#include <exception>
#include <vector>
#include <optional>

#include "Coordinates.h"
#include "../resources.h"

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
	enum class Type { Brick, Lumber, Wool, Grain, Ore, Desert, Lake, Undefined };

	Hex(Type type = Type::Undefined, std::vector<int> numbers = {});

	bool is_undefined() const { return type == Type::Undefined; }
	const Type get_type() const { return type; }
	const std::vector<int>& get_numbers() const { return numbers; }

	void set_coordinates(const Coordinates& coordinates_) { coordinates = coordinates_; }
	const Coordinates& get_coordinates() const { return coordinates; }

	void set_index(std::size_t index_) { index = index_; }
	std::size_t get_index() const { return index; }

	/* get the resource the player receives from a hex of this type */
	std::optional<resources::Resource> get_resource() const;

private:
	Type type;
	std::vector<int> numbers;
	Coordinates coordinates;
	std::size_t index;
};