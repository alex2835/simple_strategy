#pragma once

#include "Core/IAliveUnit.hpp"
#include "Core/World.hpp"
#include "Features/Actions/LandMovement.hpp"
#include "Features/Actions/MeleeAtack.hpp"

namespace sw::features
{
	constexpr int32_t SWORDSMAN_STEP = 1;

	class SwordsmanUnit final : public core::IAliveUnit
	{
		int32_t _strength = 0;
		std::unique_ptr<IAtack> _meleeAtack;
		std::unique_ptr<IMovement> _movement;

	public:
		SwordsmanUnit(int32_t id, Position pos, int32_t hp, int32_t strength) :
				IAliveUnit(id, pos, core::PositioningType::Unique, hp),
				_strength(strength),
				_meleeAtack(std::make_unique<MeleeAtack>(_strength)),
				_movement(std::make_unique<LandMovement>(SWORDSMAN_STEP))
		{}

		~SwordsmanUnit() {}

		std::string name() const override
		{
			return "Swordsman";
		}

		bool doAction(core::World& world) override
		{
			if (_meleeAtack->atack(*this, world))
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
