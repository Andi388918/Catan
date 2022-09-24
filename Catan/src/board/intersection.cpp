
#include "intersection.h"

#include <algorithm>
#include <functional>

#include "pair.h"

void Intersection::add_hex(const Coordinates& coordinates)
{
	hexes.push_back(coordinates);
}

void Intersection::add_neighbour(const Coordinates& coordinates)
{
	if (std::find(std::begin(neighbours), std::end(neighbours), coordinates) == std::end(neighbours))
		neighbours.push_back(coordinates);
}

void Intersection::add_building(const Building& building) 
{ 
	this->building = building;
	set_occupied();
}