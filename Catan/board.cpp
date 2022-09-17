
#include "board.h"
#include "distributions.h"
#include "hex_tile.h"

#include <iostream>

Board::Board()
{
	/* get resources and numbers that are used to initialize the random hex tiles */

	std::vector<std::vector<int>> hex_tile_numbers { Distributions::map_to_vector(Distributions::hex_tile_numbers) };
	std::vector<HexTile::Type> hex_tile_resources { Distributions::map_to_vector(Distributions::hex_tile_resources) };

	/* randomly shuffle resources and numbers */
	
	auto rng { std::default_random_engine {} };
	std::ranges::shuffle(hex_tile_resources, rng);
	std::ranges::shuffle(hex_tile_numbers, rng);

	/* get user definition of where hex tiles are, what resources and numbers they have
	   everything is random by default except the desert location (middle of the board) */

	hex_tiles = Distributions::hex_tiles;


	/*
	std::ranges::for_each(hex_tiles, [&hex_tile_resources, &hex_tile_numbers](auto& row)
		{
			std::ranges::for_each(row, [&hex_tile_resources, &hex_tile_numbers](auto& hex_tile)
				{
					if (hex_tile.is_random())
					{
						hex_tile = HexTile(hex_tile_resources.back(), hex_tile_numbers.back());
						hex_tile_resources.pop_back();
						hex_tile_numbers.pop_back();
					}
				}
			);
		}
	);
	*/

}