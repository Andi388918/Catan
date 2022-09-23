#pragma once

#include <vector>

#include "coordinates.h"
#include "intersection.h"

class Intersection;

class Path
{
public:
	Path() {}
	
	void add_intersection(const Coordinates& coordinates);

private:
	std::vector<Coordinates> intersections;
};