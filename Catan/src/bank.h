#pragma once

#include <map>
#include <algorithm>
#include <assert.h>
#include <exception>

#include "resources.h"
#include "item_deck.h"

class Bank
{
public:
	Bank
	(
		std::map<resources::Resource, ResourceCardDeck> resource_decks =
		{
			{ resources::Resource::Brick, 19 },
			{ resources::Resource::Lumber, 19 },
			{ resources::Resource::Wool, 19 },
			{ resources::Resource::Grain, 19 },
			{ resources::Resource::Ore, 19 }
		}
	) : resource_decks { resource_decks } {}

	resources::size_type get(resources::Resource resource_type, resources::size_type resource_amount);
	void add(const std::map<resources::Resource, ResourceCardDeck>& resource_decks_);

	std::map<resources::Resource, ResourceCardDeck>& get_resource_amounts() { return resource_decks; }

private:
	std::map<resources::Resource, ResourceCardDeck> resource_decks;
};

namespace building_prices
{
	static const std::map<resources::Resource, ResourceCardDeck> settlement_price
	{ 
		{ resources::Resource::Brick, 1 },
		{ resources::Resource::Lumber, 1 },
		{ resources::Resource::Wool, 1 },
		{ resources::Resource::Grain, 1 }
	};

	static const std::map<resources::Resource, ResourceCardDeck> road_price
	{
		{ resources::Resource::Brick, 1 },
		{ resources::Resource::Lumber, 1 }
	};

	bool can_be_bought_with(const std::map<resources::Resource, ResourceCardDeck>& what, const std::map<resources::Resource, ResourceCardDeck>& with);
	std::vector<resources::Resource> four_to_one_tradable_resources(const std::map<resources::Resource, ResourceCardDeck>& resource_decks);
}
