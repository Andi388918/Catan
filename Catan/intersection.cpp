
#include "intersection.h"

#include <algorithm>
#include <functional>

void Intersection::add_hex(const Hex& hex)
{
	hexes.push_back(std::cref(hex));
}

void Intersection::add_path(const Path& path)
{
	if (std::find(std::begin(paths), std::end(paths), path) == std::end(paths))
		paths.push_back(std::cref(path));
}

bool operator==(const std::reference_wrapper<const Hex>& lhs, const std::reference_wrapper<const Hex>& rhs)
{
	return lhs.get() == rhs.get();
}

bool operator==(const Intersection& lhs, const Intersection& rhs)
{
	return lhs.coords == rhs.coords;
}