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
		// Creates a game between two players
		Game(Player* player1, Player* player2);
		// Starts a game
		void start();
		// Gets the player by index (0 or 1)
		Player* getPlayer(int index);
	};
}
