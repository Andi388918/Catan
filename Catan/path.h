#pragma once

#include <utility>
#include <vector>

#include "coords.h"
#include "intersection.h"

struct Path
{
	std::pair<Coords, Coords> coord_pair;
	std::vector<std::reference_wrapper<const Intersection>> intersections;

	Path() {};
	Path(std::pair<Coords, Coords> p) : coord_pair{ p } {}
	
};