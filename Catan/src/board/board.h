
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

	std::vector<Hex> hexes;
	std::vector<Intersection> intersections;
	std::vector<Path> paths;

	void make_graph();

	void connect_intersections(
		const Coordinates& intersection_coordinates_a, 
		const Coordinates& intersection_coordinates_b, 
		const std::pair<Coordinates, Coordinates>& path_coordinates
	);

public:
	explicit Board(const std::unordered_map<Coordinates, Hex>& hexes = Distributions::hexes, HexInitializer hex_initializer = HexInitializer {});

	void build_settlement(std::size_t player_index, std::size_t intersection_index, bool connected_to_road = false);

	std::unordered_map<Coordinates, Intersection> get_intersection_map() { return intersection_map; }
	std::unordered_map<std::pair<Coordinates, Coordinates>, Path, PairHash> get_path_map() { return path_map; }
	std::unordered_map<Coordinates, Hex> get_hex_map() { return hex_map; }
};