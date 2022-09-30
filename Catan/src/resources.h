#pragma once

#include <map>

class ItemDeck;

namespace resources
{
	using size_type = std::size_t;

	enum class Resource
	{
		Brick, Lumber, Wool, Grain, Ore
	};

	class ResourceNotAvailable : public std::exception {
	public:
		using std::exception::exception;
	};
}