#pragma once

#include "board/coordinates.h"
#include <vector>

#include "bank.h"
#include "resources.h"

class Player
{
public:

	Player
	(
		std::map<resources::Resource, ResourceCardDeck> resource_decks =
		{
			{ resources::Resource::Brick, 0 },
			{ resources::Resource::Lumber, 0 },
			{ resources::Resource::Wool, 0 },
			{ resources::Resource::Grain, 0 },
			{ resources::Resource::Ore, 0 }
		}
	) 
	: resource_decks { resource_decks }, victory_points {} { }

	const std::map<resources::Resource, ResourceCardDeck>& get_resources() const { return resource_decks; }

	void add_to_resources(resources::Resource resource, resources::size_type amount);
	void pay(const std::map<resources::Resource, ResourceCardDeck>& resource_decks_);

	void add_victory_points(std::size_t victory_points_) { victory_points += victory_points_; }
	std::size_t get_victory_points() const { return victory_points; }

private:
	std::map<resources::Resource, ResourceCardDeck> resource_decks;
	std::size_t victory_points;
};