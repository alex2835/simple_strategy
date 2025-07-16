#pragma once

#include <cstdint>
#include <Core/IUnit.hpp>

namespace sw::core
{
	class IAliveUnit : public IUnit
	{
		int32_t _hp = 0;

	public:
		IAliveUnit(int32_t id, Position position, PositioningType positioningType, int32_t hp) :
				IUnit(id, position, positioningType),
				_hp(hp)
		{}

		virtual ~IAliveUnit() = default;

		int32_t getHp()
		{
			return _hp;
		}

		virtual bool isAlive() const
		{
			return _hp > 0;
		}

		virtual void takeDamage( int32_t damage )
		{
			_hp -= damage;
		}
	};
}
