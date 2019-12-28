#include "Player.h"
#include <stdexcept>

namespace BattleshipServer {

	Player::Player(Sockets::StringSocket& client, CommandParser& commandParser)
		:client(client), commandParser(commandParser) {
		currentGame = nullptr;
	}

	void Player::parseCommand(std::string command) {
		commandParser.parse(command, this);
	}

	Game* Player::getCurrentGame() {
		return currentGame;
	}

	Player* Player::getOpponent() {
		if (currentGame == nullptr) {
			throw std::logic_error("Player is not in game");
		}
		Player* player = currentGame->getPlayer(0);
		if (player == this) {
			return currentGame->getPlayer(1);
		}
		else {
			return player;
		}
	}

	void Player::sendMessage(std::string message) {
		client.writeLine(message);
	}
}
