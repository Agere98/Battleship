#pragma once
#include <StringSocket.h>
#include <CommandParser.h>

namespace BattleshipServer {

	/*
	A class representing a network player
	*/
	class Player {

	private:
		Sockets::StringSocket& client;
		CommandParser& commandParser;

	public:
		// Creates a player for the specified client socket and command parser
		Player(Sockets::StringSocket& client, CommandParser& commandParser);
		// Parses a command and applies its effect on the player
		void parseCommand(std::string command);
	};
}
