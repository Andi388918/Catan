#pragma once

#include <array>
#include <algorithm>

namespace building_prices
{
	static std::array<std::size_t, 5> settlement_price { 1, 1, 1, 1, 0 };
	static std::array<std::size_t, 5> road_price { 1, 1, 0, 0, 0 };

	bool can_be_bought_with(const std::array<std::size_t, 5>& what, const std::array<std::size_t, 5>& with);
}

class Bank
{
public:
	enum class Resource
	{
		Brick, Lumber, Wool, Grain, Ore
	};

	Bank() 
	{
		resource_amounts.fill(19);
	}

	std::size_t get(Resource resource, std::size_t amount)
	{
		std::size_t index { static_cast<std::size_t>(resource) };
		std::size_t available_amount { resource_amounts.at(index) };
		if (amount > available_amount) amount = available_amount;
		resource_amounts.at(index) -= amount;
		return amount;
	}

	void add(Resource resource, std::size_t amount)
	{
		std::size_t index { static_cast<std::size_t>(resource) };
		resource_amounts.at(index) += amount;
	}

private:
	std::array<std::size_t, 5> resource_amounts;

};