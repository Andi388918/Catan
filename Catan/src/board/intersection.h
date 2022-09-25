#pragma once

#include <vector>
#include <set>

#include "hex.h"
#include "coordinates.h"
#include "path.h"
#include "building.h"

class Path;

class Intersection
{
public:
	Intersection() : coordinates {}, index {}, occupied{} { }
	Intersection(const Coordinates& coordinates, std::size_t index) : coordinates { coordinates }, index { index }, occupied { false } {};

	void add_hex(std::size_t hex_index);
	void add_neighbour(std::size_t neigbour_index);
	void add_path(std::size_t path_index);
	void add_building(const Building& building);

	bool has_building() const { return building.has_value(); }
	const std::set<std::size_t>& get_neighbours() const { return neighbours; }
	const Coordinates& get_coordinates() const { return coordinates; }

	std::size_t get_index() const { return index; }
	bool is_occupied() const { return occupied; }
	void set_occupied() { this->occupied = true; }

private:
	Coordinates coordinates;
	std::size_t index;

	std::set<std::size_t> hexes;
	std::set<std::size_t> neighbours;
	std::set<std::size_t> paths;

	std::optional<Building> building;
	bool occupied;
};