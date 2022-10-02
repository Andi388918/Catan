#pragma once

#include <functional>

#include "resources.h"

class ItemDeck
{
public:
	explicit ItemDeck(resources::size_type number_of_items_) : number_of_items{ number_of_items_ } { }

	virtual resources::size_type get(resources::size_type amount) = 0;
	virtual void add(resources::size_type amount) = 0;
	const resources::size_type& get_number_of_items() const { return number_of_items; }

	void operator+=(const ItemDeck& rhs);
	void operator-=(const ItemDeck& rhs);

protected:
	friend std::ostream& operator<<(std::ostream& os, const ItemDeck& item_deck);
	friend bool operator>(const ItemDeck& lhs, const ItemDeck& rhs);

	resources::size_type number_of_items;
};

class ResourceCardDeck : public ItemDeck
{
public:
	ResourceCardDeck(resources::size_type number_of_items) : ItemDeck(number_of_items) {};

	resources::size_type get(resources::size_type amount) override;
	void add(resources::size_type amount) override;
};