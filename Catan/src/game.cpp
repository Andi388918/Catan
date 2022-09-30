
#include "game.h"
#include "printing.h"
#include "resources.h"

#include <random>

Game::Game(std::size_t nr_of_players) : board{ nr_of_players }, players { nr_of_players }, current_player_index {}
{
	buildable_settlements = std::vector<std::vector<bool>>(board.get_intersections().size(), std::vector<bool>(3));
	buildable_roads = std::vector<std::vector<bool>>(board.get_paths().size(), std::vector<bool>(3));

	build_settlement(12, 0, true);
	build_settlement(27, 1, true);
	build_settlement(46, 2, true);

	build_settlement(33, 0, true);
	build_settlement(1, 1, true);
	build_settlement(25, 2, true);
}

bool Game::is_finished()
{
	return std::ranges::any_of(players, [](const Player& player)
		{
			return player.get_victory_points() >= 10;
		}
	);
}

void Game::start_round()
{
	static std::default_random_engine ran;
	int random_number { std::uniform_int_distribution<>{2, 12}(ran) };

	std::ranges::for_each(settlements_by_hex_number.at(random_number - 2), [this](const auto& pair)
		{
			if (pair.second != Hex::Type::Desert)
			{
				std::size_t received_amount { bank.get(static_cast<resources::Resource>(pair.second), 1) };
				players.at(pair.first).add_to_resources(static_cast<resources::Resource>(pair.second), received_amount);
			}
		}
	);
}

void Game::move(int action)
{
	if (action == -1)
	{
		increase_player_index();
		start_round();
	}
	else if (action >= 0 && action < 54)
	{
		build_settlement(action, current_player_index);
	}
	else if (action >= 54 && action < 126)
	{
		build_road(action - 54, current_player_index);
	}
	else if (action >= 126 && action <= 130)
	{
		resources::Resource resource_type{ resources::Resource{ action - 126 } };
		resources::size_type resource_amount{ 4 };
		const std::map<resources::Resource, ResourceCardDeck> to_pay { { resource_type, resource_amount } };

		players.at(current_player_index).pay(to_pay);
		bank.add(to_pay);

		temporary_actions = { 131, 132, 133, 134, 135 };
	}
	else if (action >= 131 && action <= 135)
	{
		resources::Resource resource_type { action - 131 };
		resources::size_type resource_amount{ bank.get(resource_type, 1) };

		players.at(current_player_index).add_to_resources(resource_type, resource_amount);
		temporary_actions.clear();
	}
}

void Game::increase_player_index()
{
	++current_player_index;
	current_player_index %= players.size();
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

void Game::build_settlement(std::size_t intersection_index, std::size_t player_index, bool free)
{
	if (!free)
	{
		players.at(player_index).pay(building_prices::settlement_price);
		bank.add(building_prices::settlement_price);
	}
	board.build_settlement(intersection_index, player_index);
	players.at(player_index).add_victory_points(1);

	const std::vector<Intersection>& intersections { board.get_intersections() };
	const std::vector<Hex>& hexes { board.get_hexes() };
	const std::vector<Path>& paths { board.get_paths() };

	const Intersection& intersection { intersections.at(intersection_index) };

	std::fill(buildable_settlements.at(intersection_index).begin(),
		buildable_settlements.at(intersection_index).end(),
		false);

	std::ranges::for_each(intersection.get_neighboring_hexes(), [this, &player_index, &hexes](std::size_t hex_index)
		{
			const Hex& hex { hexes.at(hex_index) };
			std::ranges::for_each(hex.get_numbers(), [this, &player_index, &hex](std::size_t number)
				{
					settlements_by_hex_number.at(number - 2).push_back({ player_index, hex.get_type() });
				}
			);
		}
	);

	std::ranges::for_each(intersection.get_neighboring_intersections(), [this, &player_index](std::size_t neighboring_intersection_index)
		{
			std::fill(buildable_settlements.at(neighboring_intersection_index).begin(),
				buildable_settlements.at(neighboring_intersection_index).end(),
				false);
		}
	);

	add_to_buildable_if_not_occupied(intersection.get_neighboring_paths(), buildable_roads, paths, player_index);
}

void Game::build_road(std::size_t path_index, std::size_t player_index)
{
	players.at(player_index).pay(building_prices::road_price);
	bank.add(building_prices::road_price);

	board.build_road(path_index, player_index);

	const std::vector<Intersection>& intersections{ board.get_intersections() };
	const std::vector<Path>& paths{ board.get_paths() };

	const Path& path { paths.at(path_index) };

	std::fill(buildable_roads.at(path_index).begin(),
		buildable_roads.at(path_index).end(),
		false);

	add_to_buildable_if_not_occupied(path.get_neighboring_paths(), buildable_roads, paths, player_index);
	add_to_buildable_if_not_occupied(path.get_neighboring_intersections(), buildable_settlements, intersections, player_index);
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