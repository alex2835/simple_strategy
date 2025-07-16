#pragma once

#include "Core/Vec2.hpp"

#include <cstdint>
#include <memory>
#include <optional>
#include <string>

namespace sw::core
{
	class World;

	enum class PositioningType
	{
		Unique,	 // Only one unique Unit can be in a cell
		Share
	};

	class IUnit
	{
		uint32_t _id = 0;
		Position _position;
		PositioningType _positioningType;
		std::optional<Position> _march;

	public:
		IUnit(uint32_t id, Position position, PositioningType positioningType) :
				_id(id),
				_position(position),
				_positioningType(positioningType)
		{}

		virtual ~IUnit() {};

		virtual std::string name() const = 0;

		virtual bool doAction(World&) = 0;

		uint32_t getId() const
		{
			return _id;
		}

		Position getPosition() const
		{
			return _position;
		}

		PositioningType getPositioningType() const
		{
			return _positioningType;
		}

		std::optional<Position> getMarch() const
		{
			return _march;
		}

	private:
		friend class World;

		void setPosition(Position position)
		{
			_position = position;
		}

		void setMarch(Position march)
		{
			_march = march;
		}
	};
}
