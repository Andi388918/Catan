#pragma once

#include <functional>

#include "resources.h"

class ItemDeck
{
public:
	explicit ItemDeck(resources::size_type number_of_items_) : number_of_items{ number_of_items_ } { }

	resources::size_type get(resources::size_type amount);
	void add(resources::size_type amount);

private:
	friend std::ostream& operator<<(std::ostream& os, const ItemDeck& item_deck);

	resources::size_type number_of_items;
};