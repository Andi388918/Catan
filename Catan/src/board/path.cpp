
#include "path.h"

#include <utility>

void Path::add_intersection(const Coordinates& coordinates)
{
	if (std::find(std::begin(intersections), std::end(intersections), coordinates) != std::end(intersections))
		intersections.push_back(coordinates);
}