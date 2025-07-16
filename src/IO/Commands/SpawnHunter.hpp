#pragma once

#include <cstdint>
#include <iosfwd>

#include "Core/World.hpp"
#include "Features/HunterUnit.hpp"

namespace sw::io
{
	struct SpawnHunter
	{
		constexpr static const char* Name = "SPAWN_HUNTER";

		uint32_t unitId{};
		int32_t x{};
		int32_t y{};
		int32_t hp{};
		int32_t agility{};
		int32_t strength{};
		int32_t range{};

		void execute(core::World& world) 
		{
			world.spawnUnit(std::make_shared<features::HunterUnit>(unitId, Position{x, y}, hp, agility, strength, range));
		}

		template <typename Visitor>
		void visit(Visitor& visitor)
		{
			visitor.visit("unitId", unitId);
			visitor.visit("x", x);
			visitor.visit("y", y);
			visitor.visit("hp", hp);
			visitor.visit("agility", agility);
			visitor.visit("strength", strength);
			visitor.visit("range", range);
		}
	};
}
