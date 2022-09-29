
#include "bank.h"

namespace building_prices
{
	bool can_be_bought_with(const std::vector<resources::size_type>& what, const std::vector<resources::size_type>& with)
	{
		return std::ranges::all_of(with, [&what, i = std::size_t{}](resources::size_type resource_amount) mutable
			{
				return resource_amount >= what.at(i++);
			}
		);
	}

	std::vector<resources::Resource> four_to_one_tradable_resources(const std::vector<resources::size_type>& resources)
	{
		std::vector<resources::Resource> four_to_one_tradable;

		std::ranges::for_each(resources, [&four_to_one_tradable, i = std::size_t{}](std::size_t amount) mutable
		{
			if (amount >= 4)
				four_to_one_tradable.push_back(resources::Resource(i));
			++i;
		}
		);

		return four_to_one_tradable;
	}
}

resources::size_type Bank::get(resources::Resource resource, resources::size_type amount)
{
	return resource_decks.at(static_cast<resources::size_type>(resource)).get(amount);
}

void Bank::add(resources::Resource resource, resources::size_type amount)
{
	resource_decks.at(static_cast<resources::size_type>(resource)).add(amount);
}

void Bank::add(const std::vector<resources::size_type>& resource_amounts)
{
	std::ranges::for_each(resource_amounts, [this, i = resources::size_type {}](resources::size_type amount) mutable
		{
			resource_decks.at(i++).add(amount);
		}
	);
}