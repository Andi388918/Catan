
#include "agent.h"

#include <random>

int Agent::select_move(const std::vector<int>& moves) const
{
	static std::default_random_engine ran;
	int random_number { std::uniform_int_distribution<>{0, static_cast<int>(moves.size() - 1)}(ran) };
	return moves.at(random_number);
}