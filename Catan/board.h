
#pragma once

#include <map>

#include "hex.h"
#include "intersection.h"
#include "path.h"
#include "pair.h"
#include "coords.h"

class Board
{
private:
	std::vector<Hex> hexes;
	std::unordered_map<Coords, Intersection> intersections;
	std::unordered_map<std::pair<Coords, Coords>, Path, PairHash> paths;

public:
	Board(const std::vector<Hex>& hex_tiles);
};