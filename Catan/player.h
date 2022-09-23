#pragma once

#include "coordinates.h"
#include <vector>

class Player
{
public:
	Player() {};

	void add_settlement(const Coordinates& coordinates) { settlements.push_back(coordinates); };
	void add_road(const std::pair<Coordinates, Coordinates>& coordinates_pair) { roads.push_back(coordinates_pair); };

private:
	std::vector<Coordinates> settlements;
	std::vector<std::pair<Coordinates, Coordinates>> roads;
};