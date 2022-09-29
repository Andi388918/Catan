
#include "player.h"

void Player::pay(const std::vector<resources::size_type>& resource_amounts_)
{ 
	std::ranges::for_each(resource_amounts_, [this, i = std::size_t {}](resources::size_type amount) mutable
		{
			resource_amounts.at(i++) -= amount;
		}
	);
}

void Player::pay(resources::Resource resource, resources::size_type amount)
{
	resource_amounts.at(static_cast<std::size_t>(resource)) -= amount;
}