#pragma once
#include <StringSocket.h>
#include <CommandParser.h>

namespace BattleshipServer {

	class Player {

	private:
		Sockets::StringSocket& client;
		CommandParser& commandParser;

	public:
		Player(Sockets::StringSocket& client, CommandParser& commandParser);
		void parseCommand(std::string command);
	};
}
