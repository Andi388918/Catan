#pragma once

#include <boost/functional/hash.hpp>
#include <iostream>

struct Coordinates
{
	int x;
	int y;

	Coordinates() : x {}, y {} { }
	Coordinates(int x, int y) : x { x }, y { y } {};
};

auto as_tuple(const Coordinates& c) -> decltype(auto);

Coordinates operator+(const Coordinates& a, const Coordinates& b);
bool operator==(const Coordinates& a, const Coordinates& b);

std::ostream& operator<<(std::ostream& os, const Coordinates& coords);

std::size_t hash_value(const Coordinates& c);

namespace std {
	template<> struct hash<::Coordinates> : boost::hash<::Coordinates> {};
}