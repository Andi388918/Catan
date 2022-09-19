
#include "coords.h"

auto as_tuple(const Coords& c) -> decltype(auto)
{
    return std::tie(c.x, c.y);
}

Coords operator+(const Coords& a, const Coords& b)
{
    return Coords{ a.x + b.x, a.y + b.y };
}

bool operator==(const Coords& a, const Coords& b)
{
    return as_tuple(a) == as_tuple(b);
}

std::size_t hash_value(const Coords& c)
{
    using boost::hash_value;
    return hash_value(as_tuple(c));
}