#pragma once

namespace sw::core
{
	class IUnit;
	class World;
}

namespace sw::features
{
	class IAtack
	{
	public:
		virtual bool atack(const core::IUnit& self, core::World&) = 0;
		virtual ~IAtack() {}
	};
}
