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
	Intersection() {};

	void add_hex(const Coordinates& coordinates);
	void add_path(const std::pair<Coordinates, Coordinates>& coord_pair);
	void add_building(const Building& building);

	bool has_building() { return building.has_value(); }
	std::vector<std::pair<Coordinates, Coordinates>> get_paths() { return paths; }

private:
	std::vector<Coordinates> hexes;
	std::vector<std::pair<Coordinates, Coordinates>> paths;
	std::optional<Building> building;
};