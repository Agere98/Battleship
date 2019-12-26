#pragma once
#include <string>

namespace BattleshipServer {

	class Player;

	class CommandParser {

	public:
		virtual void parse(std::string command, Player* target) = 0;
		virtual ~CommandParser() = default;
	};
}
