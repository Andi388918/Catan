#pragma once

namespace resources
{
	using size_type = std::size_t;

	static const std::size_t nr_of_resources { 5 };

	enum class Resource
	{
		Brick, Lumber, Wool, Grain, Ore
	};
}