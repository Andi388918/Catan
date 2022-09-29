
#include "hex.h"

#include <algorithm>

Hex::Hex(Type type, std::vector<int> numbers) : type{ type }, numbers{ numbers }, coordinates{}, index{}
{
	std::ranges::for_each(numbers, [](const auto& number)
		{
			if (number < 2 || number > 12) throw InvalidHexNumber{};
		}
	);
}

std::optional<resources::Resource> Hex::get_resource() const
{
	switch (type)
	{
	case Type::Brick:
		return resources::Resource::Brick;
	case Type::Lumber:
		return resources::Resource::Lumber;
	case Type::Wool:
		return resources::Resource::Wool;
	case Type::Grain:
		return resources::Resource::Grain;
	case Type::Ore:
		return resources::Resource::Ore;
	default:
		return {};
	}
}