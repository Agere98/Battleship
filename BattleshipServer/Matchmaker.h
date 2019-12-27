#pragma once
#include <Player.h>
#include <list>
#include <pthread.h>

namespace BattleshipServer {

	/*
	A simple matchmaker
	*/
	class Matchmaker {

	private:
		std::list<Player*> playerQueue;
		pthread_mutex_t queueMutex = PTHREAD_MUTEX_INITIALIZER;

		void match(Player& player1, Player& player2);
		static void* gameBehavior(void* gameInstance);

	public:
		// Adds a player to a queue for matchmaking
		void registerPlayer(Player* player);
		// Removes a registered player from matchmaking queue
		void unregisterPlayer(Player* player);
		// Processes registered players and assigns them to matches
		virtual void createMatches();
	};
}
