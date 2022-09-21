#pragma once

#include <map>

#include "coords.h"
#include "hex.h"

struct HexInitializer
{
	void operator()(std::unordered_map<Coords, Hex>& hexes);
};