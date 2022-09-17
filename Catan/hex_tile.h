
#pragma once

#include <exception>
#include <vector>
#include <algorithm>

class HexTile
{
public:
	class InvalidHexNumber : public std::exception {};
	enum class Type { brick, lumber, wool, grain, ore, desert, lake, random, invalid };

	HexTile(Type type, std::vector<int> numbers = {});

	bool is_random() { return type == Type::random; }

private:
	Type type;
	std::vector<int> numbers;
};