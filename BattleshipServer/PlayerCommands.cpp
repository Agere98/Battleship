#include "PlayerCommands.h"
#include <iostream>

namespace BattleshipServer {

	void PlayerCommands::match(Player* target) {
		matchmaker.registerPlayer(target);
		matchmaker.createMatches();
	}

	void PlayerCommands::leave(Player* target) {
		if (target->getCurrentGame() != nullptr) {
			target->leaveGame();
		}
		else {
			matchmaker.unregisterPlayer(target);
		}
	}

	PlayerCommands& PlayerCommands::instance() {
		static PlayerCommands instance;
		return instance;
	}

	void PlayerCommands::parse(std::string command, Player* target) {
		if (command == "match") {
			match(target);
			return;
		}
		if (command == "leave") {
			leave(target);
			return;
		}

		if (target->getCurrentGame() != nullptr && target->getOpponent() != nullptr) {
			target->getOpponent()->sendMessage(command);
		}
		else {
			std::cout << command << std::endl;
		}
	}
}
