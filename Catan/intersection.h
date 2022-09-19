#pragma once

#include <vector>
#include <functional>
#include <unordered_set>
#include <algorithm>
#include <iostream>

#include "hex.h"
#include "coords.h"
#include "path.h"

static const std::vector<Coords> connected_corner_offsets = {
		Coords{1, 0},
		Coords{0, 1},
		Coords{-1, 1},
		Coords{-1, 0},
		Coords{0, -1},
		Coords{1, -1}
};


bool operator==(const std::reference_wrapper<const Hex>& lhs, const std::reference_wrapper<const Hex>& rhs)
{
	return lhs.get() == rhs.get();
}

struct Intersection
{
	Coords coords;
	std::vector<std::reference_wrapper<const Hex>> hexes;
	std::vector<std::reference_wrapper<const Path>> paths;

	void add_hex(const Hex& hex) 
	{ 
		hexes.push_back(std::cref(hex));
	}

	void add_path(const Path& path)
	{
		paths.push_back(std::cref(path));
	}
};