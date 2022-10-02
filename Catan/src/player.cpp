
#include "player.h"

void Player::add_to_resources(const resources::Resource& resource_type, resources::size_type resource_amount)
{
	std::size_t index { static_cast<std::size_t>(resource_type) };
	resource_decks.at(index).add(resource_amount);
}

void Player::pay(const std::array<ResourceCardDeck, 5>& resource_decks_)
{
	resource_decks -= resource_decks_;
}

void Player::pay(const resources::Resource& resource_type, resources::size_type resource_amount)
{
	std::size_t index { static_cast<std::size_t>(resource_type) };
	resource_decks.at(index).get(resource_amount);
}