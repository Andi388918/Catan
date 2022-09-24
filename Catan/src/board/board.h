
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
	std::unordered_map<Coordinates, Hex> hex_map;
	std::unordered_map<Coordinates, Intersection> intersection_map;
	std::unordered_map<std::pair<Coordinates, Coordinates>, Path, PairHash> path_map;

	std::vector<Coordinates> hexes;
	std::vector<Coordinates> intersections;
	std::vector<std::pair<Coordinates, Coordinates>> paths;

	void make_graph();
	void build_settlement(std::size_t intersection_index, std::size_t player_index);

	void connect_intersections
	(
		const Coordinates& intersection_coordinates_a, 
		const Coordinates& intersection_coordinates_b, 
		const std::pair<Coordinates, Coordinates>& path_coordinates
	);

public:
	explicit Board
	(
		const std::unordered_map<Coordinates, Hex>& hexes = Distributions::hexes, 
		HexInitializer hex_initializer = HexInitializer {}
	);
};