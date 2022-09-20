#pragma once

#include <vector>

#include "coords.h"
#include "intersection.h"

struct Intersection;

struct Path
{
	std::pair<Coords, Coords> coord_pair;
	std::vector<std::reference_wrapper<const Intersection>> intersections;

	Path() {};
	Path(std::pair<Coords, Coords> p) : coord_pair{ p } {}
	
	void add_intersection(const Intersection& intersection);
};

bool operator==(const Path& lhs, const Path& rhs);