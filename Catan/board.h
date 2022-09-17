
#pragma once

#include <array>
#include <vector>
#include <algorithm>
#include <random>
#include <map>

#include "hex_tile.h"

class Board
{
private:
	std::vector<std::vector<HexTile>> hex_tiles;

public:
	Board();
};