#pragma once
#include <pthread.h>

namespace BattleshipServer {

	class Player;
	class Board;

	/*
	A class representing a game with two players
	*/
	class Game {

	private:
		Player* players[2];
		Board* boards[2];
		pthread_mutex_t playersMutex = PTHREAD_MUTEX_INITIALIZER;

	public:
		// Adds a player to this game and returns its index, or -1 if this game is full
		int addPlayer(Player* player);
		// Removes a player with a specified index from this game
		void removePlayer(int index);
		// Gets the player by index (0 or 1)
		Player* getPlayer(int index);
		// Gets the board by index (0 or 1)
		Board* getBoard(int index);
		// Starts a game
		void start();
	};
}
