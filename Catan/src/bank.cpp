
#include "bank.h"

bool building_prices::can_be_bought_with(const std::array<std::size_t, 5>& what, const std::array<std::size_t, 5>& with)
{
	return std::ranges::all_of(what, [&with, i = std::size_t{}](std::size_t resource_amount) mutable
		{
			return with.at(i++) >= resource_amount;
		}
	);
}

std::vector<Bank::Resource> building_prices::four_to_one_tradable_resources(const std::array<std::size_t, 5>& resources)
{
	std::vector<Bank::Resource> four_to_one_tradable;

	std::ranges::for_each(resources, [&four_to_one_tradable, i = std::size_t {}](std::size_t amount) mutable
		{
			if (amount >= 4)
				four_to_one_tradable.push_back(Bank::Resource ( i ));
			++i;
		}
	);

	return four_to_one_tradable;
}