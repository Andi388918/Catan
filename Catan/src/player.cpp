
#include "player.h"

void Player::add_to_resources(resources::Resource resource, resources::size_type amount)
{
	auto it{ resource_decks.find(resource) };
	if (it != std::end(resource_decks))
	{
		it->second.add(amount);
	}
	else
	{
		throw resources::ResourceNotAvailable{};
	}
}

void Player::pay(const std::map<resources::Resource, ResourceCardDeck>& resource_decks_)
{
	std::ranges::for_each(resource_decks_, [this](const auto& resource_deck_pair)
		{
			resources::Resource resource_type{ resource_deck_pair.first };
			resources::size_type resource_amount{ resource_deck_pair.second.get_number_of_items() };

			auto iterator{ resource_decks.find(resource_type) };

			if (iterator != std::end(resource_decks))
			{
				iterator->second.get(resource_amount);
			}
			else
			{
				throw resources::ResourceNotAvailable{};
			}
		}
	);
}