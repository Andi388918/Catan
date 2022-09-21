#pragma once

#include <vector>

#include "hex.h"
#include "coords.h"
#include "path.h"

class Path;

class Intersection
{
public:
	Intersection() {};

	void add_hex(const Coords& hex_coords);
	void add_path(const std::pair<Coords, Coords>& path_coords);

private:
	std::vector<Coords> hexes;
	std::vector<std::pair<Coords, Coords>> paths;
};