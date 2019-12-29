#include "Game.h"
#include <Player.h>
#include <ClassicBoard.h>
#include <stdexcept>

namespace BattleshipServer {

	int Game::addPlayer(Player* player) {
		pthread_mutex_lock(&playersMutex);
		for (int i = 0; i < 2; i++) {
			if (players[i] == nullptr) {
				players[i] = player;
				ready[i] = false;
				pthread_mutex_unlock(&playersMutex);
				return i;
			}
		}
		pthread_mutex_unlock(&playersMutex);
		return -1;
	}

	void Game::removePlayer(int index) {
		if (index == 0 || index == 1) {
			pthread_mutex_lock(&playersMutex);
			players[index] = nullptr;
			if (players[0] == nullptr && players[1] == nullptr) {
				pthread_mutex_lock(&turnMutex);
				pthread_cond_signal(&playerTurn);
				pthread_mutex_unlock(&turnMutex);
			}
			pthread_mutex_unlock(&playersMutex);
			sendMessage(1 - index, "opponent left");
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

	Board* Game::getBoard(int index) {
		if (index == 0 || index == 1) {
			return boards[index];
		}
		else {
			throw std::out_of_range("Index must be 0 or 1");
		}
	}

	void Game::setReady(int index) {
		if (index == 0 || index == 1) {
			pthread_mutex_lock(&playersMutex);
			ready[index] = true;
			if (ready[0] && ready[1]) {
				pthread_mutex_lock(&turnMutex);
				pthread_cond_signal(&playerTurn);
				pthread_mutex_unlock(&turnMutex);
			}
			pthread_mutex_unlock(&playersMutex);
		}
		else {
			throw std::out_of_range("Index must be 0 or 1");
		}
	}

	bool Game::getTurn(int index) {
		if (index == 0 || index == 1) {
			pthread_mutex_lock(&turnMutex);
			bool result = turn == index;
			pthread_mutex_unlock(&turnMutex);
			return result;
		}
		else {
			throw std::out_of_range("Index must be 0 or 1");
		}
	}

	void Game::endTurn() {
		if (turn < 0) {
			throw std::logic_error("End turn called before the turn started");
		}
		pthread_mutex_lock(&turnMutex);
		turn = -1;
		pthread_cond_signal(&playerTurn);
		pthread_mutex_unlock(&turnMutex);
	}

	void Game::start() {
		pthread_mutex_lock(&turnMutex);
		for (int i = 0; i < 2; i++) {
			boards[i] = new ClassicBoard();
			getPlayer(i)->sendMessage("start");
		}
		// Wait for players to end the preparation phase
		pthread_cond_wait(&playerTurn, &turnMutex);
		bool game = true;
		while (game) {
			for (int i = 0; i < 2; i++) {
				if (players[0] == nullptr && players[1] == nullptr) {
					pthread_mutex_unlock(&turnMutex);
					return;
				}
				turn = i;
				sendMessage(i, "turn");
				pthread_cond_wait(&playerTurn, &turnMutex);
				// Check for win
				if (getBoard(1 - i)->getHitpoints() == 0) {
					game = false;
					if (i > 0 || getBoard(i)->getHitpoints() > 1) {
						// No chance for draw
						break;
					}
				}
			}
		}
		turn = -1;
		pthread_mutex_unlock(&turnMutex);
		int result[2];
		for (int i = 0; i < 2; i++) {
			result[i] = boards[i]->getHitpoints();
			delete(boards[i]);
			boards[i] = nullptr;
		}
		if (result[0] > 0 && result[1] == 0) {
			sendMessage(0, "win");
			sendMessage(1, "lose");
		}
		if (result[0] == 0 && result[1] > 0) {
			sendMessage(0, "lose");
			sendMessage(1, "win");
		}
		if (result[0] == 0 && result[1] == 0) {
			sendMessage(0, "draw");
			sendMessage(1, "draw");
		}
		// Wait for players to leave the game
		pthread_mutex_lock(&playersMutex);
		pthread_mutex_lock(&turnMutex);
		if (players[0] == nullptr && players[1] == nullptr) {
			pthread_mutex_unlock(&playersMutex);
		}
		else {
			pthread_mutex_unlock(&playersMutex);
			pthread_cond_wait(&playerTurn, &turnMutex);
		}
		pthread_mutex_unlock(&turnMutex);
	}

	void Game::sendMessage(int index, std::string message) {
		if (index == 0 || index == 1) {
			pthread_mutex_lock(&playersMutex);
			if (players[index] != nullptr) {
				players[index]->sendMessage(message);
			}
			pthread_mutex_unlock(&playersMutex);
		}
		else {
			throw std::out_of_range("Index must be 0 or 1");
		}
	}
}
