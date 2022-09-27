
#include "player.h"

void Player::pay(const std::array<std::size_t, 5>& to_pay) 
{ 
	std::ranges::for_each(to_pay, [this, i = std::size_t {}](std::size_t amount) mutable
		{
			resources.at(i) -= amount;
			++i;
		}
	);
}

void Player::pay(Bank::Resource resource, std::size_t amount)
{
	resources.at(static_cast<std::size_t>(resource)) -= amount;
}