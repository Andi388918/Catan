
#pragma once

#include <map>
#include <vector>

#include "hex_tile.h"

namespace Distributions
{
	
	static std::map<HexTile::Type, int> hex_tile_resources = {
		{ HexTile::Type::ore, 3 },
		{ HexTile::Type::brick, 3 },
		{ HexTile::Type::grain, 4 },
		{ HexTile::Type::lumber, 4 },
		{ HexTile::Type::wool, 4 } };
	
	static std::map<std::vector<int>, int> hex_tile_numbers = {
		{ { 2 }, 1 },
		{ { 3 }, 2 },
		{ { 4 }, 2 },
		{ { 5 }, 2 },
		{ { 6 }, 2 },
		{ { 8 }, 2 },
		{ { 9 }, 2 },
		{ { 10 }, 2 },
		{ { 11 }, 2 },
		{ { 12 }, 1 } };

	/* user defined hex tile configuration */

	static std::vector<std::vector<HexTile>> hex_tiles
	{
		{
			HexTile(HexTile::Type::random),
			HexTile(HexTile::Type::random),
			HexTile(HexTile::Type::random)
		},
		{
			HexTile(HexTile::Type::random),
			HexTile(HexTile::Type::random),
			HexTile(HexTile::Type::random),
			HexTile(HexTile::Type::random)
		},
		{
			HexTile(HexTile::Type::random),
			HexTile(HexTile::Type::random),
			HexTile(HexTile::Type::desert, { 7 }),
			HexTile(HexTile::Type::random),
			HexTile(HexTile::Type::random)
		},
		{
			HexTile(HexTile::Type::random),
			HexTile(HexTile::Type::random),
			HexTile(HexTile::Type::random),
			HexTile(HexTile::Type::random)
		},
		{
			HexTile(HexTile::Type::random),
			HexTile(HexTile::Type::random),
			HexTile(HexTile::Type::random)
		}
	};

	/* copy K V amount of times into vector for each K */
	template<class K, class V>
	std::vector<K> map_to_vector(const std::map<K, V>& m)
	{
		std::vector<K> v;

		std::ranges::for_each(m, [&v](const auto& pair) {
			for (int i{}; i < pair.second; ++i)
				v.push_back(pair.first);
			});

		return v;
	}

}