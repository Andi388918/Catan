
#include "board.h"
#include "distributions.hpp"

#include <vector>
#include <algorithm>

template<class Key, class T, class Hash = std::hash<Key>>
void copy_map_keys_to_vector(const std::unordered_map<Key, T, Hash>& map, std::vector<Key>& vector)
{
	vector.reserve(map.size());
	std::transform(std::begin(map), std::end(map), std::back_inserter(vector),
		[](auto& pair) { return pair.first; });
}

void init_intersection_indices(std::unordered_map<Coordinates, Intersection>& intersection_map)
{
	std::ranges::for_each(intersection_map, 
		[i = std::size_t {}](auto& pair) mutable 
		{
			pair.second.set_index(i++);
		}
	);
}

Board::Board(const std::unordered_map<Coordinates, Hex>& hex_map, HexInitializer hex_initializer) : hex_map { hex_map }
{
	hex_initializer(this->hex_map);
	make_graph();
	init_intersection_indices(intersection_map);

	copy_map_keys_to_vector(this->hex_map, hexes);
	copy_map_keys_to_vector(intersection_map, intersections);
	copy_map_keys_to_vector(path_map, paths);
}

void Board::connect_intersections(
	const Coordinates& intersection_coordinates_a, 
	const Coordinates& intersection_coordinates_b,
	const std::pair<Coordinates, Coordinates>& path_coordinates
)
{
	intersection_map[intersection_coordinates_a].add_neighbour(intersection_coordinates_b);
	intersection_map[intersection_coordinates_b].add_neighbour(intersection_coordinates_a);

	path_map[path_coordinates].add_intersection(intersection_coordinates_a);
	path_map[path_coordinates].add_intersection(intersection_coordinates_b);
}

void Board::make_graph()
{
	std::size_t intersection_index;

	std::ranges::for_each(this->hex_map, [this, &intersection_index](std::pair<const Coordinates, Hex>& pair)
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

				intersection_map.insert({ intersection_coordinates, Intersection { intersection_coordinates } });
				intersection_map[intersection_coordinates].add_hex(hex_coordinates);

				Coordinates next_intersection_coordinates;

				if (i != intersection_offsets.size() - 1)
				{
					next_intersection_coordinates = hex_coordinates + intersection_offsets.at(i + 1);
				}
				else
				{
					next_intersection_coordinates = hex_coordinates + intersection_offsets.at(0);
				}
				
				intersection_map.insert({ next_intersection_coordinates, Intersection { next_intersection_coordinates } });

				std::pair<Coordinates, Coordinates> path_coordinates { intersection_coordinates, next_intersection_coordinates };
				path_map.insert({ path_coordinates, Path {} });

				connect_intersections(intersection_coordinates, next_intersection_coordinates, path_coordinates);

			}
		}
	);
}

void Board::build_settlement(std::size_t intersection_index, std::size_t player_index)
{
	Coordinates intersection_coordinates{ intersections.at(intersection_index) };
	Intersection& intersection{ intersection_map[intersection_coordinates] };

	intersection.add_building(Building{ player_index, Building::Type::Settlement });

	std::ranges::for_each(intersection.get_neighbours(), [this](const Coordinates& neighbour_coordinates)
		{
			Intersection& neighbour{ intersection_map[neighbour_coordinates] };
			neighbour.set_occupied();
		}
	);
}