
#include "item_deck.h"

#include <iostream>

std::ostream& operator<<(std::ostream& os, const ItemDeck& item_deck)
{
	return os << item_deck.number_of_items;
}

void ItemDeck::operator+=(const ItemDeck& rhs)
{
	number_of_items += rhs.get_number_of_items();
}

void ItemDeck::operator-=(const ItemDeck& rhs)
{
	number_of_items -= rhs.get_number_of_items();
}


bool operator>(const ItemDeck& lhs, const ItemDeck& rhs)
{
	return lhs.get_number_of_items() > rhs.get_number_of_items();
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
