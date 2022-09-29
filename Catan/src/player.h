#pragma once

#include "board/coordinates.h"
#include <vector>

#include "bank.h"
#include "resources.h"

class Player
{
public:

	Player() : resource_amounts (resources::nr_of_resources, 0), victory_points{} {};

	const std::vector<resources::size_type>& get_resources() const { return resource_amounts; }

	void add_to_resources(resources::Resource resource, resources::size_type amount) { resource_amounts.at(static_cast<resources::size_type>(resource)) += amount; }
	void pay(const std::vector<resources::size_type>& resource_amounts);
	void pay(resources::Resource resource, resources::size_type amount);

	void add_victory_points(std::size_t victory_points_) { victory_points += victory_points_; }
	std::size_t get_victory_points() const { return victory_points; }

private:
	std::vector<resources::size_type> resource_amounts;
	std::size_t victory_points;
};