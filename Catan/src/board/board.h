
#pragma once

#include <map>

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

	void make_graph(
		std::unordered_map<Coordinates, Hex>& hex_map,
		std::unordered_map<Coordinates, Intersection>& intersection_map,
		std::unordered_map<std::pair<Coordinates, Coordinates>, Path, PairHash>& path_map
	);
	void build_settlement(std::size_t intersection_index, std::size_t player_index);

public:
	explicit Board
	(
		const std::unordered_map<Coordinates, Hex>& hex_map_ = Distributions::hexes, 
		HexInitializer hex_initializer = HexInitializer {}
	);
};