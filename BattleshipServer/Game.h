#pragma once
#include <string>
#include <pthread.h>

namespace BattleshipServer {

	class Player;
	class Board;

	/*
	A class representing a game with two players
	*/
	class Game {

	private:
		int turn = -1;
		Player* players[2];
		Board* boards[2];
		bool ready[2];
		pthread_mutex_t playersMutex = PTHREAD_MUTEX_INITIALIZER;
		pthread_mutex_t turnMutex = PTHREAD_MUTEX_INITIALIZER;
		pthread_cond_t playerTurn = PTHREAD_COND_INITIALIZER;

	public:
		// Adds a player to this game and returns its index, or -1 if this game is full
		int addPlayer(Player* player);
		// Removes a player with a specified index from this game
		void removePlayer(int index);
		// Gets the player by index (0 or 1)
		Player* getPlayer(int index);
		// Gets the board by index (0 or 1)
		Board* getBoard(int index);
		// Signals this game that a player finished his preparation phase
		void setReady(int index);
		// Returns true if a player with a specified index can take his turn, false otherwise
		bool getTurn(int index);
		// Signals this game that a player finished his turn
		void endTurn();
		// Starts a game
		void start();
		// Sends a message to a player with a specified index
		void sendMessage(int index, std::string message);
	};
}
