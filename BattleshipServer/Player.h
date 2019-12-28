#pragma once
#include <StringSocket.h>
#include <CommandParser.h>
#include <Game.h>

namespace BattleshipServer {

	/*
	A class representing a network player
	*/
	class Player {

	private:
		Sockets::StringSocket& client;
		CommandParser& commandParser;
		Game* currentGame;
		int gameIndex;

	public:
		// Creates a player for the specified client socket and command parser
		Player(Sockets::StringSocket& client, CommandParser& commandParser);
		// Parses a command and applies its effect on the player
		void parseCommand(std::string command);
		// Adds this player to a game
		bool joinGame(Game* game);
		// Removes this player from current game
		void leaveGame();
		// Gets the game instance that this player is participating in, returns null if player is not in game
		Game* getCurrentGame();
		// Gets the in-game index of this player
		int getIndex();
		// Gets the opponent player from this player's current game
		Player* getOpponent();
		// Sends a message string to this player
		void sendMessage(std::string message);
	};
}
