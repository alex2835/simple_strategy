#pragma once
#include <random>

namespace sw::helpers
{
	int32_t randInt(int32_t upperBound)
	{
		static std::random_device rd;
		static std::mt19937 gen(rd());
		static std::uniform_int_distribution<> dist(0, upperBound);
		return dist(gen);
	}

	bool isInRage(Position cur, Position target, int32_t range)
	{
		int32_t dx = std::abs(cur.x - target.x);
		int32_t dy = std::abs(cur.y - target.y);
		return dx <= range and dy <= range;
	}
}
