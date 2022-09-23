
#include "coordinates.h"

#include <tuple>

auto as_tuple(const Coordinates& c) -> decltype(auto)
{
    return std::tie(c.x, c.y);
}

Coordinates operator+(const Coordinates& a, const Coordinates& b)
{
    return Coordinates{ a.x + b.x, a.y + b.y };
}

bool operator==(const Coordinates& a, const Coordinates& b)
{
    return as_tuple(a) == as_tuple(b);
}

std::ostream& operator<<(std::ostream& os, const Coordinates& coords)
{
    return os << "(" << coords.x << ", " << coords.y << ")";
}

std::size_t hash_value(const Coordinates& c)
{
    using boost::hash_value;
    return hash_value(as_tuple(c));
}