#pragma once

#include "Core/IAliveUnit.hpp"
#include "Core/World.hpp"
#include "Features/Actions/LandMovement.hpp"
#include "Features/Actions/MeleeAtack.hpp"
#include "Features/Actions/RangeAtack.hpp"

namespace sw::features
{
	constexpr int32_t HUNTER_STEP = 1;

	class HunterUnit final : public core::IAliveUnit
	{
		uint32_t _agility;
		uint32_t _strength;
		uint32_t _range;
		std::unique_ptr<IAtack> _meleeAtack;
		std::unique_ptr<IAtack> _rangeAtack;
		std::unique_ptr<IMovement> _movement;

	public:
		HunterUnit(uint32_t id, Position pos, uint32_t hp, uint32_t agility, uint32_t strength, uint32_t range) :
				IAliveUnit(id, pos, core::PositioningType::Unique, hp),
				_agility(agility),
				_strength(strength),
				_range(range),
				_meleeAtack(std::make_unique<MeleeAtack>(_strength)),
				_rangeAtack(std::make_unique<RangeAtack>(_agility, _range)),
				_movement(std::make_unique<LandMovement>(HUNTER_STEP))

		{}

		~HunterUnit() {}

		std::string name() const override
		{
			return "Hunter";
		}

		bool doAction(core::World& world) override
		{
			if (_meleeAtack->atack(*this, world))
			{
				return true;
			}
			else if (_rangeAtack->atack(*this, world))
			{
				return true;
			}
			else if (_movement->move(*this, world))
			{
				return true;
			}
			return false;
		}
	};

}
