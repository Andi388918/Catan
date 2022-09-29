#pragma once

#include <vector>

#include "coordinates.h"
#include "hex.h"

struct HexInitializer
{
	void operator()(std::vector<Hex>& hexes);
};