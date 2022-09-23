
#include "hex.h"

#include <algorithm>

Hex::Hex(Type type, std::vector<int> numbers) : type { type }, numbers { numbers }
{
	std::ranges::for_each(numbers, [](const auto& number) 
		{
			if (number < 2 || number > 12) throw InvalidHexNumber{}; 
		}
	);
}