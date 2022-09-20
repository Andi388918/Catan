
#include "hex.h"

#include <algorithm>

Hex::Hex(Type type, Coords coords, std::vector<int> numbers) : type { type }, coords { coords }, numbers { numbers }
{
	std::ranges::for_each(numbers, [](const auto& number) 
		{
			if (!(2 <= number <= 12)) throw InvalidHexNumber{}; 
		}
	);
}