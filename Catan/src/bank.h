#pragma once

#include <array>
#include <algorithm>
#include <vector>

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

	std::array<std::size_t, 5>& get_resource_amounts() { return resource_amounts; }

	void add(Resource resource, std::size_t amount)
	{
		std::size_t index { static_cast<std::size_t>(resource) };
		resource_amounts.at(index) += amount;
	}

	void add(const std::array<std::size_t, 5>& resources)
	{
		std::ranges::for_each(resources, [this, i = std::size_t{}](std::size_t amount) mutable
			{
				resource_amounts.at(i++) += amount;
			}
		);
	}

private:
	std::array<std::size_t, 5> resource_amounts;

};

namespace building_prices
{
	static std::array<std::size_t, 5> settlement_price{ 1, 1, 1, 1, 0 };
	static std::array<std::size_t, 5> road_price{ 1, 1, 0, 0, 0 };

	bool can_be_bought_with(const std::array<std::size_t, 5>& what, const std::array<std::size_t, 5>& with);
	std::vector<Bank::Resource> four_to_one_tradable_resources(const std::array<std::size_t, 5>& resources);
}
