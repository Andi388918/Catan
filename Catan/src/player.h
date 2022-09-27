#pragma once

#include "board/coordinates.h"
#include <array>
#include "bank.h"

class Player
{
public:
	Player() : resources{}, victory_points {} {};

	const std::array<std::size_t, 5>& get_resources() const { return resources; }

	void add_to_resources(Bank::Resource resource, std::size_t amount) { resources.at(static_cast<std::size_t>(resource)) += amount; }
	void pay(const std::array<std::size_t, 5>& to_pay);
	void pay(Bank::Resource resource, std::size_t amount);

	void add_victory_points(std::size_t victory_points_) { victory_points += victory_points_; }
	std::size_t get_victory_points() const { return victory_points; }

private:
	std::array<std::size_t, 5> resources;
	std::size_t victory_points;
};