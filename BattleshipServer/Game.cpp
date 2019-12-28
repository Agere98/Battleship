#include "Game.h"
#include <Player.h>
#include <stdexcept>

namespace BattleshipServer {

	int Game::addPlayer(Player* player) {
		for (int i = 0; i < 2; i++) {
			if (players[i] == nullptr) {
				players[i] = player;
				return i;
			}
		}
		return -1;
	}

	void Game::removePlayer(int index) {
		if (index == 0 || index == 1) {
			players[index] = nullptr;
		}
		else {
			throw std::out_of_range("Index must be 0 or 1");
		}
	}

	Player* Game::getPlayer(int index) {
		if (index == 0 || index == 1) {
			return players[index];
		}
		else {
			throw std::out_of_range("Index must be 0 or 1");
		}
	}

	void Game::start() {
		while (true);
	}
}
