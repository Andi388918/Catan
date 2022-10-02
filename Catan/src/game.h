#pragma once

#include <vector>
#include <functional>
#include <algorithm>
#include <map>
#include <string>
#include <iostream>

#include "board/board.h"
#include "board/distributions.hpp"
#include "player.h"
#include "bank.h"
#include "random_device.h"

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
	std::vector<int> temporary_actions;

	/* function maps */
	std::map <std::string, std::function<void(int)>> make_action_functions;
	std::map <std::string, std::function<std::vector<int>()>> legal_action_functions;
	std::map <std::string, std::pair<int, int>> action_ranges;




	std::vector<std::vector<bool>> buildable_settlements;
	std::vector<std::vector<bool>> buildable_roads;
	std::map<std::size_t, std::vector<std::pair<std::size_t, resources::Resource>>> settlements_built_at_hex;

	void increase_player_index();
	void start_next_round(int action);
	void collect_resources(int number);
	void create_action_ranges();
	void trade_four_for_one(int action);
	void receive_resource_from_bank(int action);

	void buy_settlement(std::size_t intersection_index);
	void buy_road(std::size_t path_index);
	void build_settlement(std::size_t intersection_index);
	void build_road(std::size_t path_index);

	void transfer_resources_from_player_to_bank(std::size_t player_index, const std::array<ResourceCardDeck, 5>& resource_decks);
	void transfer_resources_from_player_to_bank(std::size_t player_index, const resources::Resource& resource_type, resources::size_type resource_amount);
	void transfer_resources_from_bank_to_player(std::size_t player_index, const resources::Resource& resource_type, resources::size_type resource_amount);

	std::vector<int> get_next_round_action();
	std::vector<int> get_settlement_actions();
	std::vector<int> get_road_actions();
	std::vector<int> get_four_for_one_actions();
};