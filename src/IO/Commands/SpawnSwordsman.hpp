#pragma once

#include <cstdint>
#include <iosfwd>

#include "Core/World.hpp"
#include "Features/SwordsmanUnit.hpp"

namespace sw::io
{
	struct SpawnSwordsman
	{
		constexpr static const char* Name = "SPAWN_SWORDSMAN";

		uint32_t unitId{};
		int32_t x{};
		int32_t y{};
		int32_t hp{};
		int32_t strength{};

		void execute(core::World& world)
		{
			world.spawnUnit(std::make_shared<features::SwordsmanUnit>(unitId, Position{x, y}, hp, strength));
		}

		template <typename Visitor>
		void visit(Visitor& visitor)
		{
			visitor.visit("unitId", unitId);
			visitor.visit("x", x);
			visitor.visit("y", y);
			visitor.visit("hp", hp);
			visitor.visit("strength", strength);
		}
	};
}
