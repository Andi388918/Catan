
#include "board.h"
#include "distributions.hpp"

#include <vector>
#include <algorithm>

Board::Board(const std::unordered_map<Coordinates, Hex>& hexes, HexInitializer hex_initializer) : hexes { hexes }
{
	hex_initializer(this->hexes);
	make_graph();
}

void Board::connect_intersections(
	const Coordinates& intersection_coordinates_a, 
	const Coordinates& intersection_coordinates_b,
	const std::pair<Coordinates, Coordinates>& path_coordinates
)
{
	intersections[intersection_coordinates_a].add_path(path_coordinates);
	intersections[intersection_coordinates_b].add_path(path_coordinates);

	paths[path_coordinates].add_intersection(intersection_coordinates_a);
	paths[path_coordinates].add_intersection(intersection_coordinates_b);
}

void Board::make_graph()
{
	std::ranges::for_each(hexes, [this](std::pair<const Coordinates, Hex>& pair)
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

				intersections.insert({ intersection_coordinates, Intersection {} });
				intersections[intersection_coordinates].add_hex(hex_coordinates);

				Coordinates next_intersection_coordinates;

				if (i != intersection_offsets.size() - 1)
				{
					next_intersection_coordinates = hex_coordinates + intersection_offsets.at(i + 1);
				}
				else
				{
					next_intersection_coordinates = hex_coordinates + intersection_offsets.at(0);
				}
				
				intersections.insert({ next_intersection_coordinates, Intersection {} });

				std::pair<Coordinates, Coordinates> path_coordinates { intersection_coordinates, next_intersection_coordinates };
				paths.insert({ path_coordinates, Path {} });

				connect_intersections(intersection_coordinates, next_intersection_coordinates, path_coordinates);
			}
		}
	);
}