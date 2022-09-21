#pragma once

#include "coords.h"
#include <vector>

class Player
{
public:
	Player() {};

	void add_settlement(const Coords& coords) { settlements.push_back(coords); };
	void add_road(const std::pair<Coords, Coords>& coord_pair) { roads.push_back(coord_pair); };

private:
	std::vector<Coords> settlements;
	std::vector<std::pair<Coords, Coords>> roads;
};