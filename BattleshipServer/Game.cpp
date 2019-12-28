#include "Game.h"
#include <Player.h>
#include <stdexcept>

namespace BattleshipServer {

	Game::Game(Player* player1, Player* player2) {
		players[0] = player1;
		players[1] = player2;
		player1->currentGame = this;
		player2->currentGame = this;
	}

	void Game::start() {
		while (true);
	}

	Player* Game::getPlayer(int index) {
		if (index == 0 || index == 1) {
			return players[index];
		}
		else {
			throw std::out_of_range("Index must be 0 or 1");
		}
	}
}
