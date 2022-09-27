#pragma once

#include <vector>

#include "board/board.h"
#include "board/distributions.hpp"
#include "player.h"
#include "bank.h"

class Game
{
public:
	explicit Game(std::size_t nr_of_players);
	void move(int action);

	const Board& get_board() const { return board; }
	std::vector<int>& get_legal_actions() const;

	void increase_player_index();
	bool is_finished();

	void build_settlement(std::size_t intersection_index, std::size_t player_index);

private:
	Board board;
	Bank bank;

	std::vector<Player> players;
	std::size_t current_player_index;

	std::vector<std::vector<bool>> buildable_settlements;
	std::vector<std::vector<bool>> buildable_roads;
	std::array<std::vector<std::pair<std::size_t, Hex::Type>>, 11> settlements_by_hex_number;

	void start_round();
};