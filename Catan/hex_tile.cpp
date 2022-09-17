
#include "hex_tile.h"

HexTile::HexTile(Type type, std::vector<int> numbers) : type { type }, numbers { numbers }
{
	std::ranges::for_each(numbers, [](const auto& number) 
		{
			if (!(2 <= number <= 12)) throw InvalidHexNumber{}; 
		}
	);
}