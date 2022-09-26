
#pragma once

#include <map>
#include <array>

#include "pair.h"
#include "hex.h"
#include "intersection.h"
#include "path.h"
#include "coordinates.h"
#include "distributions.hpp"
#include "hex_initializer.h"

class Board
{
private:
	std::vector<Intersection> intersections;
	std::vector<Path> paths;
	std::vector<Hex> hexes;

	std::vector<std::vector<bool>> buildable_settlements;
	std::vector<std::vector<bool>> buildable_roads;

	void make_graph(
		std::unordered_map<Coordinates, Hex>& hex_map,
		std::unordered_map<Coordinates, Intersection>& intersection_map,
		std::unordered_map<std::pair<Coordinates, Coordinates>, Path, PairHash>& path_map
	);

	void build_settlement(std::size_t intersection_index, std::size_t player_index);
	void build_road(std::size_t road_index, std::size_t player_index);

public:
	explicit Board
	(
		std::size_t nr_of_players,
		const std::unordered_map<Coordinates, Hex>& hex_map_ = Distributions::hexes,
		HexInitializer hex_initializer = HexInitializer {}
	);
};