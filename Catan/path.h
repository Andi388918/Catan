#pragma once

#include <vector>

#include "coords.h"
#include "intersection.h"

class Intersection;

class Path
{
public:
	Path() {}
	
	void add_intersection(const Coords& intersection_coords);

private:
	std::pair<Coords, Coords> coord_pair;
	std::vector<Coords> intersections;
};