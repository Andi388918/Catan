
#include "pair.h"

bool operator==(const std::pair<Coords, Coords>& lhs, const std::pair<Coords, Coords>& rhs)
{
	return lhs.first == rhs.first && lhs.second == rhs.second
		|| lhs.second == rhs.first && lhs.first == rhs.second;
}