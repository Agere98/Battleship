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
			pthread_mutex_unlock(&playersMutex);
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
				pthread_cond_signal(&playerTurn);
			}
			pthread_mutex_unlock(&playersMutex);
		}
		else {
			throw std::out_of_range("Index must be 0 or 1");
		}
	}

	bool Game::getTurn(int index) {
		if (index == 0 || index == 1) {
			return turn == index;
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
		for (int i = 0; i < 2; i++) {
			boards[i] = new ClassicBoard();
			getPlayer(i)->sendMessage("start");
		}
		pthread_mutex_lock(&turnMutex);
		pthread_cond_wait(&playerTurn, &turnMutex);
		while (true) {
			for (int i = 0; i < 2; i++) {
				turn = i;
				getPlayer(i)->sendMessage("turn");
				pthread_cond_wait(&playerTurn, &turnMutex);
			}
		}
		turn = -1;
		pthread_mutex_unlock(&turnMutex);
		for (int i = 0; i < 2; i++) {
			delete(boards[i]);
			boards[i] = nullptr;
		}
	}
}
