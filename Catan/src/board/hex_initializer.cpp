
#include "hex_initializer.h"

#include <random>

#include "distributions.hpp"

void HexInitializer::operator()(std::vector<Hex>& hexes)
{
	std::vector<std::vector<int>> hex_numbers { Distributions::copy_keys_value_amount_of_times(Distributions::hex_numbers) };
	std::vector<Hex::Type> hex_resources { Distributions::copy_keys_value_amount_of_times(Distributions::hex_resources) };

	/* randomly shuffle resources and numbers */

	auto rng{ std::default_random_engine {} };
	std::ranges::shuffle(hex_resources, rng);
	std::ranges::shuffle(hex_numbers, rng);

	std::ranges::for_each(hexes, [&hex_resources, &hex_numbers](Hex& hex)
		{
			/* initialize hex */

			if (hex.is_undefined())
			{
				hex = Hex(hex_resources.back(), hex_numbers.back());
				hex_resources.pop_back();
				hex_numbers.pop_back();
			}
		}
	);

}