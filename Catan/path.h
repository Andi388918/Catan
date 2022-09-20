#pragma once

#include <vector>

#include "coords.h"
#include "intersection.h"

struct Intersection;

struct Path
{
	std::pair<Coords, Coords> coord_pair;
	std::vector<Coords> intersections;

	Path() {}
	Path(std::pair<Coords, Coords> p) : coord_pair { p } {}
	
	void add_intersection(const Coords& intersection_coords);
};