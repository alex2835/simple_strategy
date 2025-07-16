#pragma once

#include <cstdint>

namespace sw
{
	struct IntVec2
	{
		int32_t x = 0;
		int32_t y = 0;

		bool operator==(const IntVec2& other) const
		{
			return x == other.x and y == other.y;
		}
	};

	using Position = IntVec2;
};
