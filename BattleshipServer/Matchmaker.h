#pragma once
#include <Player.h>
#include <list>

namespace BattleshipServer {

	/*
	A simple matchmaker
	*/
	class Matchmaker {

	private:
		std::list<Player*> playerQueue;

		void match(Player& player1, Player& player2);
		static void* gameBehavior(void* gameInstance);

	public:
		// Registers a player for matchmaking
		void registerPlayer(Player& player);
		// Processes registered players and assigns them to matches
		virtual void createMatches();
	};
}
