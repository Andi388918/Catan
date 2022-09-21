
#include "board.h"
#include "distributions.hpp"

#include <vector>
#include <algorithm>
#include <random>

Board::Board(const std::unordered_map<Coords, Hex>& hexes) : hexes { hexes }
{
	/* get resources and numbers that are used to initialize the random hex tiles */

	std::vector<std::vector<int>> hex_numbers { Distributions::map_to_vector(Distributions::hex_numbers) };
	std::vector<Hex::Type> hex_resources { Distributions::map_to_vector(Distributions::hex_resources) };

	/* randomly shuffle resources and numbers */
	
	auto rng { std::default_random_engine {} };
	std::ranges::shuffle(hex_resources, rng);
	std::ranges::shuffle(hex_numbers, rng);

	/* build the graph */

	std::ranges::for_each(this->hexes, [this, &hex_resources, &hex_numbers](auto& pair)
		{
			/* initialize hex */

			Coords hex_coords { pair.first };
			Hex& hex { pair.second };

			if (hex.is_random())
			{
				hex = Hex(hex_resources.back(), hex_numbers.back());
				hex_resources.pop_back();
				hex_numbers.pop_back();
			}

			for (std::vector<Coords>::size_type i {}; i < intersection_offsets.size(); ++i)
			{
				/* circling the hex by adding the offsets to the hex coordinates and assigning this hex as reference to the resulting intersections */

				Coords intersection_coords { hex_coords + intersection_offsets.at(i) };

				/* this is a neighbouring hex of the intersection */

				intersections.insert({ intersection_coords, Intersection {} });
				intersections[intersection_coords].add_hex(hex_coords);

				/* add paths 
				   when circling the hex, check if next intersection would be the start, otherwise just use the next offset to get the next intersection */

				Coords next_intersection_coords { (i < intersection_offsets.size() - 1 ? intersection_offsets.at(i + 1) : intersection_offsets.at(0)) + hex_coords };
				intersections.insert({ next_intersection_coords, Intersection {} });

				std::pair<Coords, Coords> path_coords { intersection_coords, next_intersection_coords };
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