
#include "pair.h"

bool operator==(const std::pair<Coordinates, Coordinates>& lhs, const std::pair<Coordinates, Coordinates>& rhs)
{
	return lhs.first == rhs.first && lhs.second == rhs.second
		|| lhs.second == rhs.first && lhs.first == rhs.second;
}

std::ostream& operator<<(std::ostream& os, const std::pair<Coordinates, Coordinates>& coordinates_pair)
{
	return os << "(" << coordinates_pair.first << ", " << coordinates_pair.second << ")";
}