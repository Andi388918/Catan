
#include "game.h"
#include "printing.h"
#include "resources.h"

using namespace std::placeholders;

template<class ThingsToAdd, class BuildableContainer, class LookupContainer>
void add_to_buildable_if_not_occupied(ThingsToAdd& things_to_add, BuildableContainer& buildable_container, LookupContainer& lookup_container, std::size_t player_index)
{
	std::ranges::for_each(things_to_add, [&buildable_container, &lookup_container, &player_index](std::size_t neighbor_index)
		{
			if (!lookup_container.at(neighbor_index).is_occupied())
			{
				buildable_container.at(neighbor_index).at(player_index) = true;
			}
		}
	);
}

void Game::create_action_ranges()
{
	std::map<std::string, std::size_t> action_ranges_sizes
	{
		{ "next_round", 1 },
		{ "settlements", board.get_intersections().size() },
		{ "roads", board.get_paths().size()},
		{ "trade_four_for_one", 5},
		{ "receive_resource_from_bank", 5 }
	};

	action_ranges = {};

	make_action_functions =
	{
		{ "next_round", [=](auto && ...args) { return this->start_next_round(args...); }},
		{ "settlements", [=](auto && ...args) { return this->buy_settlement(args...); }},
		{ "roads", [=](auto && ...args) { return this->buy_road(args...); }},
		{ "trade_four_for_one", [=](auto && ...args) { return this->trade_four_for_one(args...); }},
		{ "receive_resource_from_bank", [=](auto && ...args) { return this->receive_resource_from_bank(args...); }}
	};

	legal_action_functions =
	{
		{ "next_round", [=](auto && ...args) { return this->get_next_round_action(args...); } },
		{ "settlements", [=](auto && ...args) { return this->get_settlement_actions(args...); }},
		{ "roads", [=](auto && ...args) { return this->get_road_actions(args...); }},
		{ "trade_four_for_one", [=](auto && ...args) { return this->get_four_for_one_actions(args...); }}
	};

	std::ranges::for_each(make_action_functions,
		[this, &action_ranges_sizes, lower_bound = int {}](const auto& name_function_pair) mutable
		{
			std::string action_range_name { name_function_pair.first };
			int action_range_size { static_cast<int>(action_ranges_sizes.find(action_range_name)->second) };

			action_ranges.insert({ action_range_name, { lower_bound, lower_bound + action_range_size} });
			lower_bound += action_range_size;
		}
	);
}

Game::Game(std::size_t nr_of_players) : board{ nr_of_players }, players { nr_of_players }, current_player_index {}
{
	buildable_settlements = std::vector<std::vector<bool>>(board.get_intersections().size(), std::vector<bool>(3));
	buildable_roads = std::vector<std::vector<bool>>(board.get_paths().size(), std::vector<bool>(3));

	build_settlement(12);
	build_settlement(33);

	increase_player_index();

	build_settlement(27);
	build_settlement(1);

	increase_player_index();

	build_settlement(46);
	build_settlement(25);

	create_action_ranges();
}

void Game::increase_player_index()
{
	++current_player_index;
	current_player_index %= players.size();
}

bool Game::is_finished()
{
	return std::ranges::any_of(players, [](const Player& player)
		{
			return player.get_victory_points() >= 10;
		}
	);
}

void Game::transfer_resources_from_player_to_bank(std::size_t player_index, const std::map<resources::Resource, ResourceCardDeck>& resource_decks)
{
	players.at(player_index).pay(resource_decks);
	bank.add(resource_decks);
}

void Game::transfer_resources_from_bank_to_player(std::size_t player_index, resources::Resource resource_type, resources::size_type resource_amount)
{
	resources::size_type receveived_resource_amount{ bank.get(resource_type, resource_amount) };
	players.at(player_index).add_to_resources(resource_type, receveived_resource_amount);
}

void Game::transfer_resources_from_player_to_bank(std::size_t player_index, resources::Resource resource_type, resources::size_type resource_amount)
{
	transfer_resources_from_player_to_bank(player_index, {{resource_type, resource_amount}});
}

void Game::collect_resources(int number)
{
	std::ranges::for_each(settlements_built_at_hex[number], [this](const std::pair<std::size_t, resources::Resource>& player_resource_pair)
		{
			transfer_resources_from_bank_to_player(player_resource_pair.first, player_resource_pair.second, 1);
		}
	);
}

void Game::start_next_round(int action)
{
	increase_player_index();
	int random_number { random_device.next() };
	collect_resources(random_number);
}

void Game::move(int action)
{
	for (auto it { make_action_functions.begin() }; it != make_action_functions.end(); ++it)
	{
		const auto& bounds { action_ranges.find(it->first)->second };
		int lower_bound = bounds.first;
		int upper_bound = bounds.second;

		if (action >= lower_bound && action < upper_bound)
		{
			it->second(action - lower_bound);
		}
	}
}

void Game::trade_four_for_one(int action)
{
	resources::Resource resource_type { resources::Resource { action } };
	transfer_resources_from_player_to_bank(current_player_index, resource_type, 4);

	const auto& bounds { action_ranges.find("receive_resource_from_bank")->second };
	int lower_bound = bounds.first;
	int upper_bound = bounds.second;

	for (int i = lower_bound; i < upper_bound; ++i) temporary_actions.push_back(i);
}

void Game::receive_resource_from_bank(int action)
{
	resources::Resource resource_type { action };
	transfer_resources_from_bank_to_player(current_player_index, resource_type, 1);
	temporary_actions.clear();
}

void Game::buy_settlement(std::size_t intersection_index)
{
	transfer_resources_from_player_to_bank(current_player_index, building_prices::settlement_price);
	build_settlement(intersection_index);
}

void Game::buy_road(std::size_t path_index)
{
	transfer_resources_from_player_to_bank(current_player_index, building_prices::road_price);
	build_road(path_index);
}

std::vector<int> Game::get_next_round_action()
{
	return { 0 };
}

std::vector<int> get_actions_from_buildable(const std::vector<std::vector<bool>>& buildable, std::size_t player_index, int offset)
{
	std::vector<int> actions;

	std::ranges::for_each(buildable, [&player_index, &actions, &offset, i = std::size_t{}](const std::vector<bool>& v) mutable
	{
		if (v.at(player_index))
		{
			actions.push_back(i + offset);
		}
		++i;
	}
	);
	return actions;
}

std::vector<int> Game::get_settlement_actions()
{
	if (building_prices::can_be_bought_with(building_prices::settlement_price, players.at(current_player_index).get_resources()))
	{
		int offset { action_ranges.find("settlements")->second.first };
		return get_actions_from_buildable(buildable_settlements, current_player_index, offset);
	}

	return {};
}

std::vector<int> Game::get_road_actions()
{
	if (building_prices::can_be_bought_with(building_prices::road_price, players.at(current_player_index).get_resources()))
	{
		int offset { action_ranges.find("roads")->second.first };
		return get_actions_from_buildable(buildable_roads, current_player_index, offset);
	}

	return {};
}

std::vector<int> Game::get_four_for_one_actions()
{
	int offset { action_ranges.find("trade_four_for_one")->second.first };

	std::vector<int> actions;
	std::vector<resources::Resource> four_to_one_tradable_resources { building_prices::four_to_one_tradable_resources(players.at(current_player_index).get_resources()) };

	std::ranges::for_each(four_to_one_tradable_resources, [&actions, &offset](const resources::Resource& resource)
		{
			actions.push_back(static_cast<int>(resource) + offset);
		}
	);

	return actions;
}

void Game::build_settlement(std::size_t intersection_index)
{
	board.build_settlement(intersection_index, current_player_index);
	players.at(current_player_index).add_victory_points(1);

	const std::vector<Intersection>& intersections { board.get_intersections() };
	const std::vector<Hex>& hexes { board.get_hexes() };
	const std::vector<Path>& paths { board.get_paths() };

	const Intersection& intersection { intersections.at(intersection_index) };

	std::fill(buildable_settlements.at(intersection_index).begin(),
		buildable_settlements.at(intersection_index).end(),
		false);

	std::ranges::for_each(intersection.get_neighboring_hexes(), [this, &hexes](std::size_t hex_index)
		{
			const Hex& hex { hexes.at(hex_index) };

			std::ranges::for_each(hex.get_numbers(), [this, &hex](std::size_t number)
				{
					if (hex.get_resource().has_value())
						settlements_built_at_hex[number].push_back({ current_player_index, hex.get_resource().value() });
				}
			);
		}
	);

	std::ranges::for_each(intersection.get_neighboring_intersections(), [this](std::size_t neighboring_intersection_index)
		{
			std::fill(buildable_settlements.at(neighboring_intersection_index).begin(),
				buildable_settlements.at(neighboring_intersection_index).end(),
				false);
		}
	);

	add_to_buildable_if_not_occupied(intersection.get_neighboring_paths(), buildable_roads, paths, current_player_index);
}

void Game::build_road(std::size_t path_index)
{
	board.build_road(path_index, current_player_index);

	const std::vector<Intersection>& intersections{ board.get_intersections() };
	const std::vector<Path>& paths{ board.get_paths() };

	const Path& path { paths.at(path_index) };

	std::fill(buildable_roads.at(path_index).begin(),
		buildable_roads.at(path_index).end(),
		false);

	add_to_buildable_if_not_occupied(path.get_neighboring_paths(), buildable_roads, paths, current_player_index);
	add_to_buildable_if_not_occupied(path.get_neighboring_intersections(), buildable_settlements, intersections, current_player_index);
}

std::vector<int> Game::get_legal_actions()
{
	if (temporary_actions.size() > 0)
		return temporary_actions;

	std::vector<int> legal_actions;
	legal_actions.reserve(100);

	for (auto it { legal_action_functions.begin() }; it != legal_action_functions.end(); ++it)
	{
		std::vector<int> actions { it->second() };
		legal_actions.insert(legal_actions.end(), actions.begin(), actions.end());
	}
	/*
	std::cout << std::endl << "player " << current_player_index << ": ";
	print_resources(players.at(current_player_index).get_resources());
	std::cout << "actions: ";
	print(legal_actions);
	std::cout << "victory points: " << players.at(current_player_index).get_victory_points() << std::endl;
	std::cout << players.at(current_player_index).get_victory_points() << std::endl;
	std::cout << "bank: ";
	print(bank.get_resource_amounts());
	*/

	return legal_actions;
}

/*

void Board::build_city(std::size_t intersection_index, std::size_t player_index)
{
	Intersection& intersection{ intersections.at(intersection_index) };

	intersection.upgrade_settlement_to_city();
	buildable_cities.at(intersection_index).at(player_index) = false;

	std::ranges::for_each(intersection.get_neighboring_intersections(), [this, &player_index](std::size_t neighboring_intersection_index)
		{
			intersections.at(neighboring_intersection_index).set_occupied();

			std::fill(buildable_settlements.at(neighboring_intersection_index).begin(),
				buildable_settlements.at(neighboring_intersection_index).end(),
				false);
		}
	);
}

*/