#pragma once

#include <set>

#include "coordinates.h"
#include "intersection.h"

class Intersection;

class Path
{
public:
	Path() : index {} {}
	Path(std::size_t index) : index { index } { }
	
	void add_intersection(std::size_t intersection_index) { intersections.insert(intersection_index); };
	std::size_t get_index() const { return index; }

private:
	std::size_t index;
	std::set<std::size_t> intersections;
};