
#include "bank.h"

namespace building_prices
{
	bool can_be_bought_with(const std::array<ResourceCardDeck, 5>& what, const std::array<ResourceCardDeck, 5>& with)
	{
		for (std::size_t i = 0; i < what.size(); ++i)
		{
			if (what.at(i) > with.at(i)) return false;
		}
		return true;
	}

	std::vector<int> four_for_one_tradable_indices(const std::array<ResourceCardDeck, 5>& resource_decks, int offset)
	{
		std::vector<int> four_for_one_tradable_indices;
		four_for_one_tradable_indices.reserve(5);

		std::ranges::for_each(resource_decks, [&offset, &four_for_one_tradable_indices, i = int {}](const ResourceCardDeck& resource_card_deck)
			{
				if (resource_card_deck.get_number_of_items() >= 4) four_for_one_tradable_indices.push_back(i + offset);
			}
		);

		return four_for_one_tradable_indices;
	}
}

resources::size_type Bank::get(const resources::Resource& resource_type, resources::size_type resource_amount)
{
	std::size_t index { static_cast<std::size_t>(resource_type) };
	return resource_decks.at(index).get(resource_amount);
}

void Bank::add(const std::array<ResourceCardDeck, 5>& resource_decks_)
{
	resource_decks += resource_decks_;
}

void Bank::add(const resources::Resource& resource_type, resources::size_type resource_amount)
{
	std::size_t index { static_cast<std::size_t>(resource_type) };
	resource_decks.at(index).add(resource_amount);
}