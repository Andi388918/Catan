#pragma once

#include <vector>

#include "hex.h"
#include "coordinates.h"
#include "path.h"

class Path;

class Intersection
{
public:
	Intersection() {};

	void add_hex(const Coordinates& coordinates);
	void add_path(const std::pair<Coordinates, Coordinates>& coord_pair);

	std::vector<std::pair<Coordinates, Coordinates>> get_paths() { return paths; };

private:
	std::vector<Coordinates> hexes;
	std::vector<std::pair<Coordinates, Coordinates>> paths;
};