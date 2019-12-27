#include "PlayerCommands.h"
#include <iostream>

namespace BattleshipServer {

	PlayerCommands& PlayerCommands::instance() {
		static PlayerCommands instance;
		return instance;
	}

	void PlayerCommands::parse(std::string command, Player* target) {
		if (command == "match") {
			matchmaker.registerPlayer(target);
			matchmaker.createMatches();
		}
		else if (target->getCurrentGame() != nullptr) {
			target->getOpponent().sendMessage(command);
		}
		else {
			std::cout << command << std::endl;
		}
	}
}
