
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
	friend class Game;

	std::unordered_map<Coordinates, Hex> hexes;
	std::unordered_map<Coordinates, Intersection> intersections;
	std::unordered_map<std::pair<Coordinates, Coordinates>, Path, PairHash> paths;

	void make_graph();

	void connect_intersections(
		const Coordinates& intersection_coordinates_a, 
		const Coordinates& intersection_coordinates_b, 
		const std::pair<Coordinates, Coordinates>& path_coordinates
	);

public:
	explicit Board(const std::unordered_map<Coordinates, Hex>& hexes = Distributions::hexes, HexInitializer hex_initializer = HexInitializer {});

	std::unordered_map<Coordinates, Intersection> get_intersections() { return intersections; }
	std::unordered_map<std::pair<Coordinates, Coordinates>, Path, PairHash> get_paths() { return paths; }
	std::unordered_map<Coordinates, Hex> get_hexes() { return hexes; }
};