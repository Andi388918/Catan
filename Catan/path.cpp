
#include "path.h"

#include <utility>

void Path::add_intersection(const Coords& coords)
{
	if (std::find(std::begin(intersections), std::end(intersections), coords) != std::end(intersections))
		intersections.push_back(coords);
}