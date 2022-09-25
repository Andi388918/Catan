
#include "board.h"
#include "distributions.hpp"

#include <vector>
#include <algorithm>

template<class Key, class T, class Hash = std::hash<Key>>
void copy_values_from_map(const std::unordered_map<Key, T, Hash>& map, std::vector<T>& vector)
{
	vector.resize(map.size());
	std::transform(map.begin(), map.end(), std::back_inserter(vector),
		[](auto& pair) { return pair.second; }
	);
}

Board::Board(const std::unordered_map<Coordinates, Hex>& hex_map_, HexInitializer hex_initializer)
{
	std::unordered_map<Coordinates, Hex> hex_map { hex_map_ };
	std::unordered_map<Coordinates, Intersection> intersection_map;
	std::unordered_map<std::pair<Coordinates, Coordinates>, Path, PairHash> path_map;
	
	hex_initializer(hex_map);
	make_graph(hex_map, intersection_map, path_map);

	copy_values_from_map(intersection_map, intersections);
	copy_values_from_map(path_map, paths);
}

void connect_intersections(
	const Coordinates& intersection_coordinates_a, 
	const Coordinates& intersection_coordinates_b,
	const std::pair<Coordinates, Coordinates>& path_coordinates,
	std::unordered_map<Coordinates, Intersection>& intersection_map,
	std::unordered_map<std::pair<Coordinates, Coordinates>, Path, PairHash>& path_map
)
{
	std::size_t intersection_index_a { intersection_map[intersection_coordinates_a].get_index() };
	std::size_t intersection_index_b { intersection_map[intersection_coordinates_b].get_index() };
	std::size_t path_index { path_map[path_coordinates].get_index() };

	intersection_map[intersection_coordinates_a].add_neighbour(intersection_index_b);
	intersection_map[intersection_coordinates_b].add_neighbour(intersection_index_a);

	intersection_map[intersection_coordinates_a].add_path(path_index);
	intersection_map[intersection_coordinates_b].add_path(path_index);

	path_map[path_coordinates].add_intersection(intersection_index_a);
	path_map[path_coordinates].add_intersection(intersection_index_b);
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

				intersection_map[intersection_coordinates].add_hex(hex_index);

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
}

/*
void Board::build_settlement(std::size_t intersection_index, std::size_t player_index)
{
	auto pair { std::ranges::find_if(intersection_map, [intersection_index](const auto& pair) { return pair.second.get_index() == intersection_index; }) };

	Intersection& intersection { pair->second };

	intersection.add_building(Building { player_index, Building::Type::Settlement } );

	std::ranges::for_each(intersection.get_neighbours(), [this](const Coordinates& neighbour_coordinates)
		{
			Intersection& neighbour { intersection_map[neighbour_coordinates] };
			neighbour.set_occupied();
		}
	);
}
*/