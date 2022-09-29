#pragma once

#include <vector>

#include "hex.h"
#include "coordinates.h"
#include "path.h"
#include "building.h"

class Path;

class Intersection
{
public:
	Intersection() = default;
	Intersection(const Coordinates& coordinates, std::size_t index) : coordinates{ coordinates }, index{ index }, occupied { false } { }

	void add_neighboring_hex(std::size_t neighbouring_hex_index);
	void add_neighboring_intersection(std::size_t neighbouring_intersection_index);
	void add_neighboring_path(std::size_t neighbouring_path_index);

	void add_settlement(std::size_t player_index);
	void upgrade_settlement_to_city();

	const Coordinates& get_coordinates() const { return coordinates; }
	std::size_t get_index() const { return index; }

	const std::vector<std::size_t>& get_neighboring_intersections() const { return neighboring_intersections; }
	const std::vector<std::size_t>& get_neighboring_paths() const { return neighboring_paths; }
	const std::vector<std::size_t>& get_neighboring_hexes() const { return neighboring_hexes; }

	bool has_building() const { return building.has_value(); }
	const Building& get_building() const { return building.value(); }

	void set_occupied() { occupied = true; }
	bool is_occupied() const { return occupied; }

private:
	Coordinates coordinates;
	std::size_t index;

	std::vector<std::size_t> neighboring_hexes;
	std::vector<std::size_t> neighboring_intersections;
	std::vector<std::size_t> neighboring_paths;

	std::optional<Building> building;

	bool occupied;
};