#pragma once
#include "Core/World.hpp"
#include "Features/Actions/IAtack.hpp"

namespace sw::features
{
	class RangeAtack : public IAtack
	{
		int32_t _damage = 0;
		int32_t _range = 0;
		std::vector<core::IAliveUnit*> _EnemyAroundBuffer;

	public:
		RangeAtack(int32_t damage, int32_t range) :
				_damage(damage),
				_range(range)
		{}

		bool atack(const core::IUnit& self, core::World& world) override
		{
			auto pos = self.getPosition();
			for (auto& unit : world.getUnits())
			{
				if (self.getId() == unit->getId())
				{
					continue;
				}

				auto enemy = dynamic_cast<core::IAliveUnit*>(unit.get());
				if (not enemy)
				{
					continue;
				}
				if (helpers::isInRage(pos, enemy->getPosition(), _range))
				{
					_EnemyAroundBuffer.push_back(enemy);
				}
			}

			// Hit random enemy
			if (not _EnemyAroundBuffer.empty())
			{
				auto enemyId = helpers::randInt(_EnemyAroundBuffer.size() - 1);
				auto* enemyToHit = _EnemyAroundBuffer[enemyId];
				enemyToHit->takeDamage(_damage);

				world.logEvent(io::UnitAttacked{self.getId(), enemyToHit->getId(), _damage, enemyToHit->getHp()});
				_EnemyAroundBuffer.clear();
				return true;
			}
			return false;
		}
	};
}
