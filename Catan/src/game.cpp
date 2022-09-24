
#include "game.h"

void Game::move(int action)
{
	
}

std::vector<int> Game::get_legal_actions() const
{
	return players.at(current_player_index).get_legal_actions();
}

void Game::increase_player_index()
{
	++current_player_index;
	if (current_player_index == players.size()) current_player_index = 0;
}