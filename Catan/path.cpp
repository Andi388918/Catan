
#include "path.h"

#include <utility>

void Path::add_intersection(const Intersection& intersection)
{
	if (std::find(std::begin(intersections), std::end(intersections), intersection) != std::end(intersections))
		intersections.push_back(std::cref(intersection));
}

bool operator==(const Path& lhs, const Path& rhs)
{
	return (lhs.coord_pair == rhs.coord_pair) || 
		(lhs.coord_pair.first == rhs.coord_pair.second && 
			lhs.coord_pair.second == rhs.coord_pair.first);
}