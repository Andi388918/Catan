
#include "intersection.h"

#include <algorithm>
#include <functional>

void Intersection::add_hex(const Coords& coords)
{
	hexes.push_back(coords);
}

void Intersection::add_path(const std::pair<Coords, Coords>& coord_pair)
{
	if (std::find(std::begin(paths), std::end(paths), coord_pair) == std::end(paths))
		paths.push_back(coord_pair);
}