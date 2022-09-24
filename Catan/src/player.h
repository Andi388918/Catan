#pragma once

#include "board/coordinates.h"
#include <vector>

class Player
{
public:
	Player() {};

	void add_settlement(const Coordinates& coordinates) { settlements.push_back(coordinates); };
	void add_road(const std::pair<Coordinates, Coordinates>& coordinates_pair) { roads.push_back(coordinates_pair); };

	std::vector<int> get_legal_actions() const { return legal_actions; }

private:
	std::vector<Coordinates> settlements;
	std::vector<std::pair<Coordinates, Coordinates>> roads;

	std::vector<Coordinates> possible_settlement_intersections;
	std::vector<Coordinates> possible_city_intersections;
	std::vector<std::pair<Coordinates, Coordinates>> possible_road_paths;

	std::vector<int> legal_actions;
};