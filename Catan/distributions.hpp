
#pragma once

#include <map>
#include <vector>
#include <algorithm>

#include "hex.h"

namespace Distributions
{
	static const std::map<Hex::Type, int> hex_resources = {
		{ Hex::Type::ore, 3 },
		{ Hex::Type::brick, 3 },
		{ Hex::Type::grain, 4 },
		{ Hex::Type::lumber, 4 },
		{ Hex::Type::wool, 4 } };
	
	static const std::map<std::vector<int>, int> hex_numbers = {
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

	static const std::vector<Hex> hex_tiles
	{
		Hex(Hex::Type::random, Coords(4, -2)),
		Hex(Hex::Type::random, Coords(3, 0)),
		Hex(Hex::Type::random, Coords(2, 2)),
		Hex(Hex::Type::random, Coords(3, -3)),
		Hex(Hex::Type::random, Coords(2, -1)),
		Hex(Hex::Type::random, Coords(1, 1)),
		Hex(Hex::Type::random, Coords(0, 3)),
		Hex(Hex::Type::random, Coords(2, -4)),
		Hex(Hex::Type::random, Coords(1, -2)),
		Hex(Hex::Type::desert, Coords(0, 0), { 7 }),
		Hex(Hex::Type::random, Coords(-1, 2)),
		Hex(Hex::Type::random, Coords(-2, 4)),
		Hex(Hex::Type::random, Coords(0, -3)),
		Hex(Hex::Type::random, Coords(-1, -1)),
		Hex(Hex::Type::random, Coords(-2, 1)),
		Hex(Hex::Type::random, Coords(-3, 3)),
		Hex(Hex::Type::random, Coords(-2, -2)),
		Hex(Hex::Type::random, Coords(-3, 0)),
		Hex(Hex::Type::random, Coords(-4, 2))
	};

	/* copy K V amount of times into vector for each K */
	template<class K, class V>
	static std::vector<K> map_to_vector(const std::map<K, V>& m)
	{
		std::vector<K> v;

		std::ranges::for_each(m, [&v](const auto& pair) {
			for (int i{}; i < pair.second; ++i)
				v.push_back(pair.first);
			});

		return v;
	}

}