
#include "bank.h"

namespace building_prices
{
	bool can_be_bought_with(const std::map<resources::Resource, ResourceCardDeck>& what, const std::map<resources::Resource, ResourceCardDeck>& with)
	{
		return std::ranges::all_of(what, [&with](const auto& resource_deck_pair)
			{
				auto iterator { with.find(resource_deck_pair.first) };

				if (iterator != std::cend(with))
				{
					resources::size_type available_resource_amount { iterator->second.get_number_of_items() };
					resources::size_type price_resource_amount { resource_deck_pair.second.get_number_of_items() };

					return available_resource_amount >= price_resource_amount;
				}

				throw resources::ResourceNotAvailable {"resource not found in available resources"};
			}
		);
	}
	std::vector<resources::Resource> four_to_one_tradable_resources(const std::map<resources::Resource, ResourceCardDeck>& resource_decks)
	{
		std::vector<resources::Resource> four_to_one_tradable_resources;

		std::ranges::for_each(resource_decks, [&four_to_one_tradable_resources](const auto& resource_deck_pair)
		{
			resources::Resource resource_type { resource_deck_pair.first };
			resources::size_type resource_amount { resource_deck_pair.second.get_number_of_items() };

			if (resource_amount >= 4)
				four_to_one_tradable_resources.push_back(resource_type);
		}
		);

		return four_to_one_tradable_resources;
	}
}

resources::size_type Bank::get(resources::Resource resource, resources::size_type amount)
{
	auto iterator { resource_decks.find(resource) };

	if (iterator != std::end(resource_decks))
	{
		return iterator->second.get(amount);
	}

	throw resources::ResourceNotAvailable {};
}

void Bank::add(const std::map<resources::Resource, ResourceCardDeck>& resource_decks_)
{
	std::ranges::for_each(resource_decks_, [this](const auto& resource_deck_pair)
		{
			resources::Resource resource_type { resource_deck_pair.first };
			resources::size_type resource_amount { resource_deck_pair.second.get_number_of_items() };

			auto iterator { resource_decks.find(resource_type) };

			if (iterator != std::end(resource_decks))
			{
				iterator->second.add(resource_amount);
			}
			else
			{
				throw resources::ResourceNotAvailable{};
			}
		}
	);
}