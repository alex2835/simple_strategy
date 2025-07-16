#pragma once

#include "details/CommandParserVisitor.hpp"

#include <functional>
#include <sstream>
#include <string>

namespace sw::io
{
	class CommandParser
	{
	private:
		std::unordered_map<std::string, std::function<void(std::istream&)>> _commands;

	public:
		template <class TCommandData, class TCommandExecutor>
		CommandParser& add(TCommandExecutor& executor)
		{
			std::string commandName = TCommandData::Name;
			auto [it, inserted] = _commands.emplace(
				commandName,
				[&executor](std::istream& stream)
				{
					TCommandData data;
					CommandParserVisitor visitor(stream);
					data.visit(visitor);
					executor(std::move(data));
				});
			if (!inserted)
			{
				throw std::runtime_error("Command already exists: " + commandName);
			}

			return *this;
		}

		void parse(std::istream& stream);
	};
}
