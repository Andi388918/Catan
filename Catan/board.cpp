
#include "board.h"
#include "distributions.h"
#include "hex.h"
#include "intersection.h"
#include "path.h"

#include <iostream>

struct PairHash {
public:
	template <typename T, typename U>
	std::size_t operator()(const std::pair<T, U>& x) const
	{
		return std::hash<T>()(x.first) ^ std::hash<U>()(x.second);
	}
};

Board::Board(std::vector<Hex> hexes) : hexes { hexes }
{
	/* get resources and numbers that are used to initialize the random hex tiles */

	std::vector<std::vector<int>> hex_numbers { Distributions::map_to_vector(Distributions::hex_numbers) };
	std::vector<Hex::Type> hex_resources { Distributions::map_to_vector(Distributions::hex_resources) };

	/* randomly shuffle resources and numbers */
	
	auto rng { std::default_random_engine {} };
	std::ranges::shuffle(hex_resources, rng);
	std::ranges::shuffle(hex_numbers, rng);

	std::unordered_map<Coords, Intersection> intersections;

	std::ranges::for_each(hexes, [&intersections](const Hex& hex)
		{
			std::array<Coords, 6> offsets = hex.intersections();

			std::ranges::for_each(offsets, [&intersections, &hex](const Coords& coords)
				{
					intersections[coords].add_hex(hex);
				}
			);
		}
	);

	std::unordered_map<std::pair<Coords, Coords>, Path, PairHash> paths;

	std::ranges::for_each(intersections, [&intersections, &paths](const auto& pair)
		{
			std::ranges::for_each(connected_corner_offsets, [&pair, &intersections, &paths](const auto& offset)
				{
					Coords coords { pair.first + offset };

					if (intersections.find(coords) != std::end(intersections))
					{
						paths[{ coords, coords + offset}] = Path { { coords, coords + offset } };
					}
				}
			);
		}
	);

	std::ranges::for_each(paths, [&paths, &intersections](auto& pair)
		{
			Intersection& intersection1 { intersections[pair.first.first] };
			Intersection& intersection2 { intersections[pair.first.second] };

			intersection1.add_path(pair.second);
			intersection2.add_path(pair.second);			
		}
	);

	/* get user definition of where hex tiles are, what resources and numbers they have
	   everything is random by default except the desert location (middle of the board) */

	/*
	std::ranges::for_each(hexes, [&hex_resources, &hex_numbers](auto& row)
		{
			std::ranges::for_each(row, [&hex_resources, &hex_numbers](auto& hex)
				{
					if (hex.is_random())
					{
						hex = HexTile(hex_resources.back(), hex_numbers.back());
						hex_resources.pop_back();
						hex_numbers.pop_back();
					}
				}
			);
		}
	);
	*/

}