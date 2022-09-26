
#include "board.h"
#include "distributions.hpp"

#include <vector>
#include <algorithm>
#include <iostream>

/* helper functions */

template<class Key, class T, class Hash = std::hash<Key>>
void copy_values_from_map(const std::unordered_map<Key, T, Hash>& map, std::vector<T>& vector)
{
	vector.reserve(map.size());
	std::transform(map.begin(), map.end(), std::back_inserter(vector),
		[](auto& pair) { return pair.second; }
	);
}

template<class ThingsToAdd, class BuildableContainer, class LookupContainer>
void add_to_buildable_if_not_occupied(ThingsToAdd& things_to_add, BuildableContainer& buildable_container, LookupContainer& lookup_container, std::size_t player_index)
{
	std::ranges::for_each(things_to_add, [&buildable_container, &lookup_container, &player_index](std::size_t neighbor_index)
		{
			if (!lookup_container.at(neighbor_index).is_occupied())
			{
				buildable_container.at(neighbor_index).at(player_index) = true;
			}
		}
	);
}

void connect_intersections(
	const Coordinates& intersection_coordinates_a,
	const Coordinates& intersection_coordinates_b,
	const std::pair<Coordinates, Coordinates>& path_coordinates,
	std::unordered_map<Coordinates, Intersection>& intersection_map,
	std::unordered_map<std::pair<Coordinates, Coordinates>, Path, PairHash>& path_map
)
{
	Intersection& intersection_a{ intersection_map[intersection_coordinates_a] };
	Intersection& intersection_b{ intersection_map[intersection_coordinates_b] };
	Path& path{ path_map[path_coordinates] };

	std::size_t intersection_index_a{ intersection_a.get_index() };
	std::size_t intersection_index_b{ intersection_b.get_index() };
	std::size_t path_index{ path.get_index() };

	intersection_a.add_neighboring_intersection(intersection_index_b);
	intersection_b.add_neighboring_intersection(intersection_index_a);

	intersection_a.add_neighboring_path(path_index);
	intersection_b.add_neighboring_path(path_index);

	path.add_neighboring_intersection(intersection_index_a);
	path.add_neighboring_intersection(intersection_index_b);
}

/* member functions */

Board::Board(std::size_t nr_of_players, const std::unordered_map<Coordinates, Hex>& hex_map_, HexInitializer hex_initializer)
{
	std::unordered_map<Coordinates, Hex> hex_map { hex_map_ };
	std::unordered_map<Coordinates, Intersection> intersection_map;
	std::unordered_map<std::pair<Coordinates, Coordinates>, Path, PairHash> path_map;
	
	hex_initializer(hex_map);
	make_graph(hex_map, intersection_map, path_map);

	copy_values_from_map(intersection_map, intersections);
	copy_values_from_map(path_map, paths);
	copy_values_from_map(hex_map, hexes);

	buildable_settlements = std::vector(intersections.size(), std::vector<bool>(nr_of_players, false));
	buildable_roads = std::vector(paths.size(), std::vector<bool>(nr_of_players, false));
}

void Board::make_graph(
	std::unordered_map<Coordinates, Hex>& hex_map, 
	std::unordered_map<Coordinates, Intersection>& intersection_map,
	std::unordered_map<std::pair<Coordinates, Coordinates>, Path, PairHash>& path_map
)
{
	std::size_t intersection_index {};
	std::size_t path_index {};

	std::ranges::for_each(hex_map, [this, &intersection_map, &path_map, &intersection_index, &path_index, hex_index = std::size_t {}](std::pair<const Coordinates, Hex>& pair) mutable
		{
			Coordinates hex_coordinates { pair.first };

			/*
				for each offset: add the offset to the hex coordinates
				the resulting coordinates are the coordinates of an intersection
				add this intersection to the intersections map
				add the current hex coordinates to the intersection
				connect this intersection to the next intersection
				hex coordinates + next offset = next intersection
				if there is no next offset, use the first element of the offset container, that is, connect last to first intersection
			*/

			for (std::vector<Coordinates>::size_type i {}; i < intersection_offsets.size(); ++i)
			{
				Coordinates intersection_coordinates { hex_coordinates + intersection_offsets.at(i) };
				auto intersection_insertion_result { intersection_map.insert({ intersection_coordinates, Intersection { intersection_coordinates, intersection_index } }) };
				if (intersection_insertion_result.second) ++intersection_index;

				intersection_map[intersection_coordinates].add_neighboring_hex(hex_index++);

				Coordinates next_intersection_coordinates { (i != intersection_offsets.size() - 1 ? intersection_offsets.at(i + 1) : intersection_offsets.at(0)) + hex_coordinates };
				intersection_insertion_result = intersection_map.insert({ next_intersection_coordinates, Intersection { next_intersection_coordinates, intersection_index } });
				if (intersection_insertion_result.second) ++intersection_index;

				std::pair<Coordinates, Coordinates> path_coordinates { intersection_coordinates, next_intersection_coordinates };
				auto path_insertion_result { path_map.insert({ path_coordinates, Path { path_index } }) };
				if (path_insertion_result.second) ++path_index;

				connect_intersections(
					intersection_coordinates,
					next_intersection_coordinates,
					path_coordinates,
					intersection_map,
					path_map
				);
			}
		}
	);

	/* connect paths to their neighboring paths */

	std::ranges::for_each(paths, [this](Path& path)
		{
			std::ranges::for_each(path.get_neighboring_intersections(), [this, &path](std::size_t intersection_index)
				{
					Intersection& intersection{ intersections.at(intersection_index) };
					
					std::ranges::for_each(intersection.get_neighboring_paths(), [this, &path](std::size_t neighboring_path_index)
						{
							if (neighboring_path_index != path.get_index())
							{
								path.add_neighboring_path(neighboring_path_index);
							}
						}
					);
				}
			);
		}
	);
}

void Board::build_settlement(std::size_t intersection_index, std::size_t player_index)
{
	Intersection& intersection { intersections.at(intersection_index) };
	intersection.add_settlement(player_index);

	std::fill(buildable_settlements.at(intersection_index).begin(),
		buildable_settlements.at(intersection_index).end(),
		false);

	std::ranges::for_each(intersection.get_neighboring_intersections(), [this, &player_index](std::size_t neighboring_intersection_index)
		{
			intersections.at(neighboring_intersection_index).set_occupied();
			
			std::fill(buildable_settlements.at(neighboring_intersection_index).begin(), 
				buildable_settlements.at(neighboring_intersection_index).end(), 
				false);
		}
	);

	add_to_buildable_if_not_occupied(intersection.get_neighboring_paths(), buildable_roads, paths, player_index);
}

void Board::build_road(std::size_t path_index, std::size_t player_index)
{
	Path& path { paths.at(path_index) };
	path.add_road(player_index);

	std::fill(buildable_settlements.at(path_index).begin(),
		buildable_settlements.at(path_index).end(),
		false);

	add_to_buildable_if_not_occupied(path.get_neighboring_intersections(), buildable_settlements, intersections, player_index);
	add_to_buildable_if_not_occupied(path.get_neighboring_paths(), buildable_roads, paths, player_index);
}