#pragma once

#include <utility>

#include "coords.h"

struct PairHash {
	template <class T, class U>
	std::size_t operator()(const std::pair<T, U>& x) const
	{
		return std::hash<T>()(x.first) ^ std::hash<U>()(x.second);
	}
};

bool operator==(const std::pair<Coords, Coords>& lhs, const std::pair<Coords, Coords>& rhs);