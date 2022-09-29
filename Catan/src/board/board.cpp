
#include "board.h"

#include <algorithm>
#include <iostream>

/* helper functions */

template<class Key, class T, class Hash = std::hash<Key>>
void copy_ordered_values_from_map(const std::unordered_map<Key, T, Hash>& map, std::vector<T>& vector)
{
	vector.resize(map.size());
	std::ranges::for_each(map, [&vector](const auto& pair)
		{
			vector.at(pair.second.get_index()) = pair.second;
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

	Board::size_type intersection_index_a{ intersection_a.get_index() };
	Board::size_type intersection_index_b{ intersection_b.get_index() };
	Board::size_type path_index{ path.get_index() };

	intersection_a.add_neighboring_intersection(intersection_index_b);
	intersection_b.add_neighboring_intersection(intersection_index_a);

	intersection_a.add_neighboring_path(path_index);
	intersection_b.add_neighboring_path(path_index);

	path.add_neighboring_intersection(intersection_index_a);
	path.add_neighboring_intersection(intersection_index_b);
}

void Board::connect_path_to_neighboring_paths(Path& path)
{
	std::ranges::for_each(path.get_neighboring_intersections(), [this, &path](size_type intersection_index)
		{
			Intersection& intersection { intersections.at(intersection_index) };

			std::ranges::for_each(intersection.get_neighboring_paths(), [this, &path](size_type neighboring_path_index)
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

/* member functions */

Board::Board(size_type nr_of_players, std::unordered_map<Coordinates, Hex> hex_map, HexInitializer hex_initializer)
{
	make_graph(hex_map);
	hex_initializer(hexes);
}

void Board::make_graph(
	std::unordered_map<Coordinates, Hex>& hex_map
)
{
	std::unordered_map<Coordinates, Intersection> intersection_map;
	std::unordered_map<std::pair<Coordinates, Coordinates>, Path, PairHash> path_map;

	size_type intersection_index {};
	size_type path_index {};

	std::ranges::for_each(hex_map, [this, &intersection_map, &path_map, &intersection_index, &path_index, hex_index = size_type {}](std::pair<const Coordinates, Hex>& pair) mutable
		{
			Coordinates hex_coordinates { pair.first };
			Hex& hex { pair.second };

			hex.set_coordinates(hex_coordinates);
			hex.set_index(hex_index);

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

				intersection_map[intersection_coordinates].add_neighboring_hex(hex_index);

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

			++hex_index;
		}
	);

	copy_ordered_values_from_map(intersection_map, intersections);
	copy_ordered_values_from_map(path_map, paths);
	copy_ordered_values_from_map(hex_map, hexes);

	std::ranges::for_each(paths, [this](Path& path)
		{
			connect_path_to_neighboring_paths(path);
		}
	);
}

void Board::build_settlement(size_type intersection_index, size_type player_index)
{
	Intersection& intersection { intersections.at(intersection_index) };
	intersection.add_settlement(player_index);

	std::ranges::for_each(intersection.get_neighboring_intersections(), [this](size_type neighboring_intersection_index)
		{
			intersections.at(neighboring_intersection_index).set_occupied();
		}
	);
}

void Board::build_road(size_type path_index, size_type player_index)
{
	Path& path { paths.at(path_index) };
	path.add_road(player_index);
}

void Board::build_city(size_type intersection_index, size_type player_index)
{
	intersections.at(intersection_index).upgrade_settlement_to_city();
}