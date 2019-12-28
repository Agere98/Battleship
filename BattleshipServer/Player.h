#pragma once
#include <StringSocket.h>
#include <CommandParser.h>
#include <Game.h>

namespace BattleshipServer {

	/*
	A class representing a network player
	*/
	class Player {

		friend class Game;

	private:
		Sockets::StringSocket& client;
		CommandParser& commandParser;
		Game* currentGame;

	public:
		// Creates a player for the specified client socket and command parser
		Player(Sockets::StringSocket& client, CommandParser& commandParser);
		// Parses a command and applies its effect on the player
		void parseCommand(std::string command);
		// Gets the game instance that this player is participating in, returns null if player is not in game
		Game* getCurrentGame();
		// Gets the opponent player from this player's current game
		Player* getOpponent();
		// Sends a message string to this player
		void sendMessage(std::string message);
	};
}
