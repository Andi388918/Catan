#pragma once

class Building
{
public:
	enum class Type { Settlement, City, Road };
	Building(std::size_t owned_by_player_index) : owned_by_player_index { owned_by_player_index }, type { type }  {}

private:
	std::size_t owned_by_player_index;
	Type type;
};