#pragma once

#include "Core/World.hpp"

#include <cstdint>
#include <iosfwd>

namespace sw::io
{
	struct March
	{
		constexpr static const char* Name = "MARCH";

		uint32_t unitId{};
		int32_t targetX{};
		int32_t targetY{};

		void execute(core::World& world)
		{
			world.setUnitMarch(unitId, Position{targetX, targetY});
		}

		template <typename Visitor>
		void visit(Visitor& visitor)
		{
			visitor.visit("unitId", unitId);
			visitor.visit("targetX", targetX);
			visitor.visit("targetY", targetY);
		}
	};
}
