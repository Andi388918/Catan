#pragma once

#include <vector>

#include "board.h"
#include "distributions.hpp"
#include "player.h"

class Game
{
public:
	Game(std::size_t nr_of_players) : players(nr_of_players) {};
	void move(int action);

private:
	Board board;
	std::vector<Player> players;
};