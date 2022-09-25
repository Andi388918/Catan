
#include "intersection.h"

#include <algorithm>
#include <functional>

#include "pair.h"

void Intersection::add_hex(std::size_t hex_index)
{
	hexes.insert(hex_index);
}

void Intersection::add_neighbour(std::size_t neighbour_index)
{
		neighbours.insert(neighbour_index);
}

void Intersection::add_path(std::size_t path_index)
{
		paths.insert(path_index);
}

void Intersection::add_building(const Building& building) 
{ 
	this->building = building;
	set_occupied();
}