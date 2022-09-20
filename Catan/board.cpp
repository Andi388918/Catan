
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
			/* everything is random by default except the desert location (middle of the board) */

			Coords hex_coords { pair.first };

			if (pair.second.type == Hex::Type::random)
			{
				pair.second = Hex(hex_resources.back(), hex_numbers.back());
				hex_resources.pop_back();
				hex_numbers.pop_back();
			}

			for (std::vector<Coords>::size_type i {}; i < intersection_offsets.size(); ++i)
			{
				/* circling the hex by adding the offsets to the hex coordinates and assigning this hex as reference to the resulting intersections */

				Coords intersection_coords { hex_coords + intersection_offsets.at(i) };
				intersections.insert({ intersection_coords, Intersection { intersection_coords } });
				Intersection& intersection { intersections[intersection_coords] };
				intersection.add_hex(hex_coords);

				/* add paths */

				/* when circling the hex, check if next intersection would be the start, otherwise just use the next offset to get the next intersection */

				Coords next_intersection_coords { (i < intersection_offsets.size() - 1 ? intersection_offsets.at(i + 1) : intersection_offsets.at(0)) + hex_coords };

				intersections.insert({ next_intersection_coords, Intersection { next_intersection_coords } });
				Intersection& next_intersection { intersections[next_intersection_coords] };

				paths.insert({ { intersection_coords, next_intersection_coords }, Path { {intersection_coords, next_intersection_coords} } });
				Path& path { paths[{ intersection_coords, next_intersection_coords }] };

				/* add path to adjacent intersections and add these intersections to the path */

				intersection.add_path(path.coord_pair);
				next_intersection.add_path(path.coord_pair);

				path.add_intersection(intersection.coords);
				path.add_intersection(next_intersection.coords);
			}
		}
	);
}