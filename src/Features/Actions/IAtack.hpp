#pragma once


namespace sw::features
{
	class core::IUnit;
	class core::World;

	class IAtack
	{
	public:
		virtual bool atack(const core::IUnit& self, core::World&) = 0;
	};
}
