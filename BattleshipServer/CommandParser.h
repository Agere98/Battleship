#pragma once
#include <string>

namespace BattleshipServer {

	class Player;

	/*
	Base class for parsing command strings
	*/
	class CommandParser {

	public:
		// Parses a command and applies its effect on the target
		virtual void parse(std::string command, Player* target) = 0;
		virtual ~CommandParser() = default;
	};
}
