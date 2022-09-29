
#include "item_deck.h"

#include <iostream>

resources::size_type ItemDeck::get(resources::size_type amount)
{
	resources::size_type received = amount > number_of_items ? number_of_items : amount;
	number_of_items -= received;
	return received;
}

void ItemDeck::add(resources::size_type amount)
{
	number_of_items += amount;
}

std::ostream& operator<<(std::ostream& os, const ItemDeck& item_deck)
{
	return os << item_deck.number_of_items;
}