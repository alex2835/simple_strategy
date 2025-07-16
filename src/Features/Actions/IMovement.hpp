#pragma once

namespace sw::features
{
	class IMovement
	{
	public:
		virtual bool move(core::IUnit& self, core::World&) = 0;
		virtual ~IMovement() {}
	};
}
