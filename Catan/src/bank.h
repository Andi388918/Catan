#pragma once

#include <algorithm>
#include <exception>
#include <array>
#include <vector>
#include <iterator>

#include "resources.h"
#include "item_deck.h"

class Bank
{
public:
	Bank() : resource_decks { 19, 19, 19, 19, 19 } {}

	resources::size_type get(const resources::Resource& resource_type, resources::size_type resource_amount);
	void add(const std::array<ResourceCardDeck, 5>& resource_decks_);
	void add(const resources::Resource& resource_type, resources::size_type resource_amount);

	const std::array<ResourceCardDeck, 5>& get_resource_amounts() const { return resource_decks; }

private:
	std::array<ResourceCardDeck, 5> resource_decks;
};

namespace building_prices
{
	static const std::array<ResourceCardDeck, 5> settlement_price { 1, 1, 1, 1, 0 };
	static const std::array<ResourceCardDeck, 5> road_price { 1, 1, 0, 0, 0 };

	bool can_be_bought_with(const std::array<ResourceCardDeck, 5>& what, const std::array<ResourceCardDeck, 5>& with);
	std::vector<int> four_for_one_tradable_indices(const std::array<ResourceCardDeck, 5>& resource_decks, int offset = 0);
}

/* array operators */

template<typename T, std::size_t N>
std::array<T, N>& operator+=(std::array<T, N>& lhs, const std::array<T, N>& rhs) {
	for (std::size_t i = 0; i < N; ++i)
		lhs.at(i) += rhs.at(i);
	return lhs;
}

template<typename T, std::size_t N>
std::array<T, N>& operator-=(std::array<T, N>& lhs, const std::array<T, N>& rhs) {
	for (std::size_t i = 0; i < N; ++i)
		lhs.at(i) -= rhs.at(i);
	return lhs;
}