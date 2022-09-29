#pragma once

#include <vector>
#include <algorithm>

#include "resources.h"
#include "item_deck.h"

class Bank
{
public:
	Bank() : resource_decks(resources::nr_of_resources, ItemDeck(19)) { }

	resources::size_type get(resources::Resource resource, resources::size_type amount);
	void add(resources::Resource resource, resources::size_type amount);
	void add(const std::vector<resources::size_type>& resource_amounts);

	std::vector<ItemDeck>& get_resource_amounts() { return resource_decks; }

private:
	std::vector<ItemDeck> resource_decks;
};

namespace building_prices
{
	static std::vector<resources::size_type> settlement_price { 1, 1, 1, 1, 0 };
	static std::vector<resources::size_type> road_price { 1, 1, 0, 0, 0 };

	bool can_be_bought_with(const std::vector<resources::size_type>& what, const std::vector<resources::size_type>& with);
	std::vector<resources::Resource> four_to_one_tradable_resources(const std::vector<resources::size_type>& resources);
}
