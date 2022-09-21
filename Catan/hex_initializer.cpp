
#include "hex_initializer.h"

#include <random>

#include "distributions.hpp"

void HexInitializer::operator()(std::unordered_map<Coords, Hex>& hexes)
{

	std::vector<std::vector<int>> hex_numbers { Distributions::map_to_vector(Distributions::hex_numbers) };
	std::vector<Hex::Type> hex_resources { Distributions::map_to_vector(Distributions::hex_resources) };

	assert(hexes.size() - 1 == hex_numbers.size() == hex_resources.size());

	/* randomly shuffle resources and numbers */

	auto rng{ std::default_random_engine {} };
	std::ranges::shuffle(hex_resources, rng);
	std::ranges::shuffle(hex_numbers, rng);

	std::ranges::for_each(hexes, [&hex_resources, &hex_numbers](auto& pair)
		{
			/* initialize hex */

			Hex& hex { pair.second };

			if (hex.is_undefined())
			{
				hex = Hex(hex_resources.back(), hex_numbers.back());
				hex_resources.pop_back();
				hex_numbers.pop_back();
			}
		}
	);

}