
#pragma once

#include <map>
#include <vector>

#include "pair.h"
#include "hex.h"
#include "intersection.h"
#include "path.h"
#include "coordinates.h"
#include "distributions.hpp"
#include "hex_initializer.h"

class Board
{
public:
	using size_type = std::size_t;

	explicit Board
	(
		std::size_t nr_of_players,
		std::unordered_map<Coordinates, Hex> hex_map = Distributions::hexes,
		HexInitializer hex_initializer = HexInitializer {}
	);

	void build_settlement(size_type intersection_index, size_type player_index);
	void build_road(size_type road_index, size_type player_index);
	void build_city(size_type intersection_index, size_type player_index);

	const std::vector<Hex>& get_hexes() const { return hexes; }
	const std::vector<Intersection>& get_intersections() const { return intersections; }
	const std::vector<Path>& get_paths() const { return paths; }

private:
	std::vector<Intersection> intersections;
	std::vector<Path> paths;
	std::vector<Hex> hexes;

	void make_graph(
		std::unordered_map<Coordinates, Hex>& hex_map
	);

	void connect_path_to_neighboring_paths(Path& path);
};