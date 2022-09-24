#pragma once

#include <vector>

#include "hex.h"
#include "coordinates.h"
#include "path.h"
#include "building.h"

class Path;

class Intersection
{
public:
	Intersection() : coordinates {}, index {}, occupied{} { }
	Intersection(const Coordinates& coordinates) : coordinates{ coordinates }, index{}, occupied { false } {};

	void add_hex(const Coordinates& coordinates);
	void add_neighbour(const Coordinates& coordinates);
	void add_building(const Building& building);

	bool has_building() const { return building.has_value(); }
	const std::vector<Coordinates>& get_neighbours() const { return neighbours; }
	const Coordinates& get_coordinates() const { return coordinates; }

	void set_index(std::size_t index) { this->index = index; }
	bool is_occupied() const { return occupied; }
	void set_occupied() { this->occupied = true; }

private:
	Coordinates coordinates;
	std::size_t index;

	std::vector<Coordinates> hexes;
	std::vector<Coordinates> neighbours;

	std::optional<Building> building;
	bool occupied;
};