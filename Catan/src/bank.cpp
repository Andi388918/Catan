
#include "bank.h"

bool building_prices::can_be_bought_with(const std::array<std::size_t, 5>& what, const std::array<std::size_t, 5>& with)
{
	return std::ranges::all_of(what, [&with, i = std::size_t{}](std::size_t resource_amount) mutable
		{
			return with.at(i++) >= resource_amount;
		}
	);
}