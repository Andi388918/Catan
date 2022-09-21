
#include "board.h"
#include "distributions.hpp"

#include <vector>
#include <algorithm>
#include <random>

Board::Board(const std::unordered_map<Coords, Hex>& hexes, HexInitializer hex_initializer) : hexes { hexes }
{
	hex_initializer(this->hexes);
	make_graph();
}

void Board::make_graph()
{
	std::ranges::for_each(hexes, [this](auto& pair)
		{
			Coords hex_coords{ pair.first };

			for (std::vector<Coords>::size_type i{}; i < intersection_offsets.size(); ++i)
			{
				/* circling around the hex by adding the offset to the hex coordinates and assigning this hex as reference to the resulting intersection */

				Coords intersection_coords{ hex_coords + intersection_offsets.at(i) };
				intersections.insert({ intersection_coords, Intersection {} });
				intersections[intersection_coords].add_hex(hex_coords);

				/* add paths
				   when circling the hex, check if next intersection would be the start, otherwise just use the next offset to get the next intersection */

				Coords next_intersection_coords{ (i < intersection_offsets.size() - 1 ? intersection_offsets.at(i + 1) : intersection_offsets.at(0)) + hex_coords };
				intersections.insert({ next_intersection_coords, Intersection {} });

				std::pair<Coords, Coords> path_coords{ intersection_coords, next_intersection_coords };
				paths.insert({ path_coords, Path {} });

				/* add path to adjacent intersections and add these intersections to the path */

				intersections[intersection_coords].add_path(path_coords);
				intersections[next_intersection_coords].add_path(path_coords);

				paths[path_coords].add_intersection(intersection_coords);
				paths[path_coords].add_intersection(next_intersection_coords);
			}
		}
	);
}