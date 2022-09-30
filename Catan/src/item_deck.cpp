
#include "item_deck.h"

#include <iostream>

std::ostream& operator<<(std::ostream& os, const ItemDeck& item_deck)
{
	return os << item_deck.number_of_items;
}

resources::size_type ResourceCardDeck::get(resources::size_type amount)
{
	resources::size_type received = amount > number_of_items ? number_of_items : amount;
	number_of_items -= received;
	return received;
}

void ResourceCardDeck::add(resources::size_type amount)
{
	number_of_items += amount;
}
