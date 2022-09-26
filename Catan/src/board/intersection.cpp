
#include "intersection.h"

#include <algorithm>
#include <functional>

#include "pair.h"

void Intersection::add_neighboring_hex(std::size_t neighbouring_hex_index)
{
	neighboring_hexes.push_back(neighbouring_hex_index);
}

void Intersection::add_neighboring_intersection(std::size_t neighbouring_intersection_index)
{
	if (std::ranges::find(neighboring_intersections, neighbouring_intersection_index) == neighboring_intersections.end())
		neighboring_intersections.push_back(neighbouring_intersection_index);
}

void Intersection::add_neighboring_path(std::size_t neighbouring_path_index)
{
	if (std::ranges::find(neighboring_paths, neighbouring_path_index) == neighboring_paths.end())
		neighboring_paths.push_back(neighbouring_path_index);
}

void Intersection::add_settlement(std::size_t player_index) 
{ 
	building = Building { player_index, Building::Type::Settlement };
	set_occupied();
}

void Intersection::upgrade_settlement_to_city()
{
	building = Building{ building.value().owned_by_player_index, Building::Type::City };
}