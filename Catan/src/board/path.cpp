
#include "path.h"

#include <algorithm>

void Path::add_neighboring_intersection(std::size_t neighboring_intersection_index)
{
	if (std::ranges::find(neighboring_intersections, neighboring_intersection_index) == neighboring_intersections.end())
	{
		neighboring_intersections.push_back(neighboring_intersection_index);
	}
}

void Path::add_neighboring_path(std::size_t neighboring_path_index)
{
	neighboring_paths.push_back(neighboring_path_index);
}

void Path::add_road(std::size_t player_index)
{
	road = Building { player_index, Building::Type::Road };
	set_occupied();
}