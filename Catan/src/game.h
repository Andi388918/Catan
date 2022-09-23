#pragma once

#include <vector>

#include "board/board.h"
#include "board/distributions.hpp"
#include "player.h"

class Game
{
public:
	explicit Game(std::size_t nr_of_players) : players(nr_of_players) {};
	void move(int action);

private:
	Board board;
	std::vector<Player> players;
};