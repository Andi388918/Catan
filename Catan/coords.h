#pragma once

#include <boost/functional/hash.hpp>
#include <iostream>

struct Coords
{
	int x;
	int y;

	Coords() : x {}, y {} { }
	Coords(int x, int y) : x { x }, y { y } {};
};

auto as_tuple(const Coords& c) -> decltype(auto);

Coords operator+(const Coords& a, const Coords& b);
bool operator==(const Coords& a, const Coords& b);

std::ostream& operator<<(std::ostream& os, const Coords& coords);

std::size_t hash_value(const Coords& c);

namespace std {
	template<> struct hash<::Coords> : boost::hash<::Coords> {};
}