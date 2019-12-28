#pragma once

namespace BattleshipServer {

	class Player;

	/*
	A class representing a game with two players
	*/
	class Game {

	private:
		Player* players[2];

	public:
		// Adds a player to this game and returns its index, or -1 if this game is full
		int addPlayer(Player* player);
		// Removes a player with a specified index from this game
		void removePlayer(int index);
		// Gets the player by index (0 or 1)
		Player* getPlayer(int index);
		// Starts a game
		void start();
	};
}
