#pragma once

#include <map>

#include "coordinates.h"
#include "hex.h"

struct HexInitializer
{
	void operator()(std::unordered_map<Coordinates, Hex>& hexes);
};