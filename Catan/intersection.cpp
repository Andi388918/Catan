
#include "intersection.h"

#include <algorithm>
#include <functional>

void Intersection::add_hex(const Coords& hex_coords)
{
	hexes.push_back(hex_coords);
}

void Intersection::add_path(const std::pair<Coords, Coords>& path)
{
	if (std::find(std::begin(paths), std::end(paths), path) == std::end(paths))
		paths.push_back(path);
}