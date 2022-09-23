#pragma once

#include <utility>

#include "Coordinates.h"

struct PairHash {
	template <class T, class U>
	std::size_t operator()(const std::pair<T, U>& x) const
	{
		return std::hash<T>()(x.first) ^ std::hash<U>()(x.second);
	}
};

bool operator==(const std::pair<Coordinates, Coordinates>& lhs, const std::pair<Coordinates, Coordinates>& rhs);
std::ostream& operator<<(std::ostream& os, const std::pair<Coordinates, Coordinates>& coordinates_pair);