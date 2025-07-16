#include "Core/World.hpp"

namespace sw::core
{
	const Units& World::getUnits()
	{
		return _units;
	}

	PtrIUnit& World::getUnitById(uint32_t unitId)
	{
		auto unitIter = std::ranges::find(_units, unitId, &IUnit::_id);
		if (unitIter == _units.end())
		{
			throw std::runtime_error(std::format("Error: setMarch for not existed unit {}", unitId));
		}
		return *unitIter;
	}

	void World::createMap(uint32_t width, uint32_t height)
	{
		if (_mapHeight != 0 or _mapWidth != 0)
		{
			throw std::runtime_error("Error: double map creation");
		}
		_mapWidth = width;
		_mapHeight = height;
		logEvent(io::MapCreated{width, height});
	}

	void World::spawnUnit(PtrIUnit unit)
	{
		logEvent(io::UnitSpawned{unit->getId(), unit->name(), unit->getPosition().x, unit->getPosition().y});
		_units.push_back(std::move(unit));
	}

	void World::moveUnit(IUnit& unit, Position newPos)
	{
		if (newPos.y < 0 or newPos.x < 0 or newPos.y >= _mapHeight or newPos.x >= _mapWidth)
		{
			throw std::runtime_error(std::format("Error: move unit out of bound x{}, y{}", newPos.x, newPos.y));
		}
		unit.setPosition(newPos);
		logEvent(io::UnitMoved{unit.getId(), newPos.x, newPos.y});
	}

	void World::setUnitMarch(uint32_t unitId, Position target)
	{
		auto& unit = getUnitById(unitId);
		unit->setMarch(target);
		auto unitPos = unit->getPosition();
		logEvent(io::MarchStarted{unitId, unitPos.x, unitPos.y, target.x, target.y});
	}

	bool World::simulateTick()
	{
		cleanDead();

		size_t aliveUnits = 0;
		size_t activeUnits = 0;
		for (auto& unit : _units)
		{
			const auto* aliveUnit = dynamic_cast<const IAliveUnit*>(unit.get());
			if ( aliveUnit->isAlive() )
			{
				aliveUnits++;
				activeUnits += unit->doAction(*this);
			}
		}
		_tick++;
		return aliveUnits >= 1 and activeUnits > 0;
	}

	void World::simulate()
	{
		while (simulateTick());
	}

	void World::cleanDead()
	{
		for (size_t i = 0; i < _units.size();)
		{
			const auto& unit = _units[i];
			const auto* aliveUnit = dynamic_cast<const IAliveUnit*>(unit.get());
			if (aliveUnit and not aliveUnit->isAlive())
			{
				logEvent(io::UnitDied{unit->getId()});
				_units.erase(_units.begin() + i);
			}
			else
				i++;
		}
	}

}
