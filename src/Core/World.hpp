#pragma once

#include "Core/IUnit.hpp"
#include "Core/IAliveUnit.hpp"

#include "IO/System/EventLog.hpp"
#include "IO/Events/MapCreated.hpp"
#include "IO/Events/MarchStarted.hpp"
#include "IO/Events/UnitSpawned.hpp"
#include "IO/Events/UnitAttacked.hpp"
#include "IO/Events/UnitDied.hpp"
#include "IO/Events/UnitMoved.hpp"

#include <cassert>
#include <format>
#include <memory>
#include <unordered_map>
#include <vector>

namespace sw::core
{
	using PtrIUnit = std::shared_ptr<IUnit>;
	using Units = std::vector<PtrIUnit>;

	class World
	{
		EventLog _logger; // could be DI but it's templated
		size_t _tick = 1;
		Units _units;
		uint32_t _mapHeight = 0;
		uint32_t _mapWidth = 0;

	public:
		World() = default;

		template <class TEvent>
		void logEvent(TEvent&& event)
		{
			_logger.log(_tick, std::forward<TEvent>(event));
		}

		const Units& getUnits();

		PtrIUnit& getUnitById(uint32_t unitId);

		void createMap(uint32_t width, uint32_t height);

		void spawnUnit(PtrIUnit unit);

		void setUnitMarch(uint32_t unitId, Position position);

		void moveUnit(IUnit& unit, Position newPos);

		bool simulateTick();

		void simulate();

	private:
		void cleanDead();
	};

}
