
#include "hex.h"

Hex::Hex(Type type, Coords coords, std::vector<int> numbers) : type { type }, coords { coords }, numbers { numbers }
{
	std::ranges::for_each(numbers, [](const auto& number) 
		{
			if (!(2 <= number <= 12)) throw InvalidHexNumber{}; 
		}
	);
}

std::array<Coords, 6> Hex::intersections() const
{
	std::array<Coords, 6> intersections;

	std::for_each(std::begin(intersection_offsets), std::end(intersection_offsets), [this, &intersections, i = std::size_t{}](const Coords& direction) mutable
		{
			intersections[i++] = coords + direction;
		}
	);

	return intersections;
}