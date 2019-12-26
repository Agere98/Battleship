#include "PlayerCommands.h"
#include <iostream>

namespace BattleshipServer {

	PlayerCommands& PlayerCommands::instance() {
		static PlayerCommands instance;
		return instance;
	}

	void PlayerCommands::parse(std::string command, Player* target) {
		std::cout << command << std::endl;
	}
}
