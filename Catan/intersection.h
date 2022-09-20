#pragma once

#include <vector>

#include "hex.h"
#include "coords.h"
#include "path.h"

struct Path;

struct Intersection
{
	Coords coords;
	std::vector<std::reference_wrapper<const Hex>> hexes;
	std::vector<std::reference_wrapper<const Path>> paths;

	void add_hex(const Hex& hex);
	void add_path(const Path& path);
};

bool operator==(const std::reference_wrapper<const Hex>& lhs, const std::reference_wrapper<const Hex>& rhs);
bool operator==(const Intersection& lhs, const Intersection& rhs);