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

	bool Player::joinGame(Game* game) {
		if (currentGame != nullptr) {
			throw std::logic_error("Player is already in game");
		}
		gameIndex = game->addPlayer(this);
		if (gameIndex >= 0) {
			currentGame = game;
			return true;
		}
		return false;
	}

	void Player::leaveGame() {
		if (currentGame == nullptr) {
			throw std::logic_error("Player is not in game");
		}
		currentGame->removePlayer(gameIndex);
		currentGame = nullptr;
	}

	Game* Player::getCurrentGame() {
		return currentGame;
	}

	Player* Player::getOpponent() {
		if (currentGame == nullptr) {
			throw std::logic_error("Player is not in game");
		}
		return currentGame->getPlayer(1 - gameIndex);
	}

	void Player::sendMessage(std::string message) {
		client.writeLine(message);
	}
}
