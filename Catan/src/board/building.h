#pragma once

struct Building
{
	enum class Type { Settlement, City, Road };
	Building(std::size_t owned_by_player_index, Type type) : owned_by_player_index { owned_by_player_index }, type { type }  {}

	std::size_t owned_by_player_index;
	Type type;
};