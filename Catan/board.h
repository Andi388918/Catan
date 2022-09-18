
#pragma once

#include <array>
#include <vector>
#include <algorithm>
#include <random>
#include <map>

#include "hex_tile.h"
#include "catan_graph.h"

class Board
{
private:
	catan::CatanGraph catan_graph;

public:
	Board(catan::size_type radius = 2);
};