#pragma once

#include <vector>
#include <functional>
#include <algorithm>
#include <map>

#include "board/board.h"
#include "board/distributions.hpp"
#include "player.h"
#include "bank.h"
#include "random_device.h"

struct ActionRange
{
	int lower_bound;
	int upper_bound;
	std::function<void(int)> function;

	ActionRange(int lower_bound, int upper_bound, std::function<void(int)> function)
		: lower_bound { lower_bound }, upper_bound { upper_bound }, function { function } { }
};

class Game
{
public:
	explicit Game(std::size_t nr_of_players);
	void move(int action);

	const Board& get_board() const { return board; }
	std::vector<int> get_legal_actions();

	bool is_finished();

private:
	Board board;
	Bank bank;

	std::vector<Player> players;
	std::size_t current_player_index;

	RandomDevice random_device;
	std::vector<ActionRange> action_ranges;



	std::vector<std::vector<bool>> buildable_settlements;
	std::vector<std::vector<bool>> buildable_roads;

	std::map<std::size_t, std::vector<std::pair<std::size_t, resources::Resource>>> settlements_built_at_hex;

	std::vector<int> temporary_actions;

	void increase_player_index();
	void start_next_round(int action);
	void collect_resources(int number);
	void create_action_ranges();

	void buy_settlement(std::size_t intersection_index);
	void buy_road(std::size_t path_index);

	void build_settlement(std::size_t intersection_index);
	void build_road(std::size_t path_index);

	void trade_four_for_one(int action);
	void receive_resource_from_bank(int action);

	void transfer_resources_from_player_to_bank(std::size_t player_index, const std::map<resources::Resource, ResourceCardDeck>& resource_decks);
	void transfer_resources_from_player_to_bank(std::size_t player_index, resources::Resource resource_type, resources::size_type resource_amount);
	void transfer_resources_from_bank_to_player(std::size_t player_index, resources::Resource resource_type, resources::size_type resource_amount);
};