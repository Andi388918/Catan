
#include "game.h"
#include "printing.h"
#include "resources.h"

using namespace std::placeholders;

void Game::create_action_ranges()
{
	std::multimap<int, std::function<void(int)>> action_range_function_map
	{
		{ 1, std::bind(&Game::start_next_round, this, _1) },
		{ board.get_intersections().size(), std::bind(&Game::buy_settlement, this, _1) },
		{ board.get_paths().size(), std::bind(&Game::buy_road, this, _1) },
		{ 5, std::bind(&Game::trade_four_for_one, this, _1) },
		{ 5, std::bind(&Game::receive_resource_from_bank, this, _1) }
	};

	action_ranges.reserve(action_range_function_map.size());

	std::ranges::for_each(action_range_function_map, 
		[this, last = int {}](const auto& action_range_function_pair) mutable
		{
			action_ranges.push_back(ActionRange { last, last + action_range_function_pair.first, action_range_function_pair.second });
			last += action_range_function_pair.first;
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
	for (auto it { action_ranges.begin() }; it != action_ranges.end(); ++it)
	{
		if (action >= it->lower_bound && action < it->upper_bound)
		{
			it->function(action - it->lower_bound);
		}
	}
}

void Game::trade_four_for_one(int action)
{
	resources::Resource resource_type{ resources::Resource { action } };
	transfer_resources_from_player_to_bank(current_player_index, resource_type, 4);
	temporary_actions = { 131, 132, 133, 134, 135 };
}

void Game::receive_resource_from_bank(int action)
{
	resources::Resource resource_type { action };
	transfer_resources_from_bank_to_player(current_player_index, resource_type, 1);
	temporary_actions.clear();
}

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

std::vector<int> Game::get_legal_actions()
{
	if (temporary_actions.size() > 0)
		return temporary_actions;

	std::vector<int> legal_actions;

	legal_actions.push_back(-1);

	if (building_prices::can_be_bought_with(building_prices::settlement_price, players.at(current_player_index).get_resources()))
	{
		std::vector<int> actions_settlements = get_actions_from_buildable(buildable_settlements, current_player_index, 0);
		legal_actions.insert(legal_actions.end(), actions_settlements.begin(), actions_settlements.end());
	}

	if (building_prices::can_be_bought_with(building_prices::road_price, players.at(current_player_index).get_resources()))
	{
		std::vector<int> actions_roads = get_actions_from_buildable(buildable_roads, current_player_index, 54);
		legal_actions.insert(legal_actions.end(), actions_roads.begin(), actions_roads.end());
	}

	std::vector<resources::Resource> four_to_one_tradable_resources { building_prices::four_to_one_tradable_resources(players.at(current_player_index).get_resources()) };

	if (four_to_one_tradable_resources.size() > 0)
	{
		std::ranges::for_each(four_to_one_tradable_resources, [&legal_actions](const resources::Resource& resource)
			{
				legal_actions.push_back(static_cast<std::size_t>(resource) + 126);
			}
		);
	}

	/*
	print(legal_actions);
	std::cout << std::endl << "player " << current_player_index << ": ";
	print(players.at(current_player_index).get_resources());
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