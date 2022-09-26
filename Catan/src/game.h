#pragma once

#include <vector>

#include "board/board.h"
#include "board/distributions.hpp"
#include "player.h"

class Game
{
public:
	explicit Game(std::size_t nr_of_players) : board { nr_of_players }, players(nr_of_players), current_player_index{} {};
	void move(int action);

	Board get_board() { return board; }
	std::vector<int> get_legal_actions() const;

	void increase_player_index();

private:
	Board board;
	std::vector<Player> players;
	std::size_t current_player_index;
};