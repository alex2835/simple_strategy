#pragma once

#include "Core/World.hpp"
#include "Features/Actions/IMovement.hpp"

namespace sw::features
{
	class LandMovement : public IMovement
	{
		int32_t _step = 0;

	public:
		LandMovement(int32_t step) :
				_step(step)
		{}

		bool move(core::IUnit& self, core::World& world) override
		{
			auto pos = self.getPosition();
			auto target = self.getMarch();
			if (not target or target == pos)
			{
				return false;
			}

			if (pos.x < target->x)
			{
				pos.x += std::min(_step, target->x - pos.x);
			}
			else if (pos.x > target->x)
			{
				pos.x -= std::min(_step, pos.x - target->x);
			}
			if (pos.y < target->y)
			{
				pos.y += std::min(_step, target->y - pos.y);
			}
			else if (pos.y > target->y)
			{
				pos.y -= std::min(_step, pos.y - target->y);
			}
			world.moveUnit(self, pos);
			return true;
		}
	};
}
