#include "Matchmaker.h"
#include <Game.h>
#include <stdexcept>

namespace BattleshipServer {

	void Matchmaker::match(Player* player1, Player* player2) {
		Game* game = new Game();
		player1->joinGame(game);
		player2->joinGame(game);
		pthread_t thread;
		pthread_create(&thread, NULL, Matchmaker::gameBehavior, (void*)game);
	}

	void* Matchmaker::gameBehavior(void* gameInstance) {
		pthread_detach(pthread_self());
		Game* game = (Game*)gameInstance;
		game->start();
		delete(game);
		pthread_exit(NULL);
	}

	void Matchmaker::registerPlayer(Player* player) {
		if (player == nullptr) {
			throw std::invalid_argument("Player is null");
		}
		pthread_mutex_lock(&queueMutex);
		playerQueue.insert(player);
		pthread_mutex_unlock(&queueMutex);
	}

	void Matchmaker::unregisterPlayer(Player* player) {
		if (player == nullptr) {
			return;
		}
		pthread_mutex_lock(&queueMutex);
		playerQueue.erase(player);
		pthread_mutex_unlock(&queueMutex);
	}

	void Matchmaker::createMatches() {
		pthread_mutex_lock(&queueMutex);
		while (playerQueue.size() >= 2) {
			Player* player1 = *playerQueue.begin();
			playerQueue.erase(player1);
			Player* player2 = *playerQueue.begin();
			playerQueue.erase(player2);
			match(player1, player2);
		}
		pthread_mutex_unlock(&queueMutex);
	}
}
