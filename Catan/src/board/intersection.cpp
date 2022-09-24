
#include "intersection.h"

#include <algorithm>
#include <functional>

#include "pair.h"

void Intersection::add_hex(const Coordinates& coordinates)
{
	hexes.push_back(coordinates);
}

void Intersection::add_path(const std::pair<Coordinates, Coordinates>& coordinates_pair)
{
	if (std::find(std::begin(paths), std::end(paths), coordinates_pair) == std::end(paths))
		paths.push_back(coordinates_pair);
}

void Intersection::add_building(const Building& building) 
{ 
	this->building = building; 
}