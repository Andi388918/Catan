#pragma once

#include "board/coordinates.h"
#include <vector>

#include "bank.h"
#include "resources.h"

class Player
{
public:

	Player () 
	: resource_decks { 0, 0, 0, 0, 0 }, victory_points {} { }

	const std::array<ResourceCardDeck, 5>& get_resources() const { return resource_decks; }

	void add_to_resources(const resources::Resource& resource_type, resources::size_type resource_amount);
	void pay(const std::array<ResourceCardDeck, 5>& resource_decks_);
	void pay(const resources::Resource& resource_type, resources::size_type resource_amount);

	void add_victory_points(std::size_t victory_points_) { victory_points += victory_points_; }
	std::size_t get_victory_points() const { return victory_points; }

private:
	std::array<ResourceCardDeck, 5> resource_decks;
	std::size_t victory_points;
};