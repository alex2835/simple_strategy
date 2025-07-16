#pragma once

#include "World.hpp"

namespace sw::core
{
	class CommandImmediateExecutor
	{
	private:
		World& _world;

	public:
		CommandImmediateExecutor(World& world) :
				_world(world)
		{}

		template <class TCommand>
		void operator()(TCommand&& command)
		{
			command.execute(_world);
		}
	};
}
