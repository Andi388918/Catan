#pragma once

#include <vector>

#include "coordinates.h"
#include "intersection.h"
#include "building.h"

class Intersection;

class Path
{
public:
	Path() = default;
	Path(std::size_t index) : index{ index }, occupied { false } { }
	
	void add_neighboring_intersection(std::size_t neighboring_intersection_index);
	void add_neighboring_path(std::size_t neighboring_path_index);

	void add_road(std::size_t player_index);

	std::size_t get_index() const { return index; }
	bool has_road() const { return road.has_value(); }

	const std::vector<std::size_t>& get_neighboring_intersections() const { return neighboring_intersections; }
	const std::vector<std::size_t>& get_neighboring_paths() const { return neighboring_paths; }

	void set_occupied() { occupied = true; }
	bool is_occupied() const { return occupied; }

private:
	std::size_t index;
	std::vector<std::size_t> neighboring_intersections;
	std::vector<std::size_t> neighboring_paths;
	std::optional<Building> road;

	bool occupied;
};