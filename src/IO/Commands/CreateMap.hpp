#pragma once

#include "Core/World.hpp"

#include <cstdint>
#include <iosfwd>

namespace sw::io
{
	struct CreateMap
	{
		constexpr static const char* Name = "CREATE_MAP";

		uint32_t width{};
		uint32_t height{};

		void execute(core::World& world)
		{
			world.createMap(width, height);
		}

		template <typename Visitor>
		void visit(Visitor& visitor)
		{
			visitor.visit("width", width);
			visitor.visit("height", height);
		}
	};
}
