
#include "path.h"

#include <utility>

void Path::add_intersection(const Coords& intersection_coords)
{
	if (std::find(std::begin(intersections), std::end(intersections), intersection_coords) != std::end(intersections))
		intersections.push_back(intersection_coords);
}