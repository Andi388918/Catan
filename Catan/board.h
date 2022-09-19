
#pragma once

#include <array>
#include <vector>
#include <algorithm>
#include <random>
#include <map>

#include "hex.h"

class Board
{
private:
	std::vector<Hex> hexes;

public:
	Board(std::vector<Hex> hex_tiles);
};