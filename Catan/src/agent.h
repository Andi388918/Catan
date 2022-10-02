#pragma once

#include <vector>

struct Agent
{
	int select_move(const std::vector<int>& moves) const;
};