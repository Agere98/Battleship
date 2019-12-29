#include "PlayerCommands.h"
#include <Board.h>
#include <string>
#include <sstream>
#include <iostream>

namespace BattleshipServer {

	void PlayerCommands::match(Player* target) {
		if (target->getCurrentGame() != nullptr) {
			invalidCommand(target);
			return;
		}
		matchmaker.registerPlayer(target);
		target->sendMessage("matchmaking");
		matchmaker.createMatches();
	}

	void PlayerCommands::leave(Player* target) {
		if (target->getCurrentGame() != nullptr) {
			target->leaveGame();
		}
		else {
			matchmaker.unregisterPlayer(target);
		}
		target->sendMessage("left");
	}

	void PlayerCommands::ships(Player* target, std::string args) {
		if (target->getCurrentGame() == nullptr) {
			invalidCommand(target);
			return;
		}
		Board* board = target->getCurrentGame()->getBoard(target->getIndex());
		if (board == nullptr) {
			invalidCommand(target);
			return;
		}
		std::stringstream argStream(args);
		for (int i = 0; i < (int)board->getShipSizes().size(); i++) {
			int x, y;
			char orientation;
			argStream >> x >> y >> orientation;
			if (argStream.fail() || x < 0 || x >= board->getWidth() || y < 0 || y >= board->getHeight()
				|| !(orientation == 'v' || orientation == 'h')) {
				invalidCommand(target);
				board->clear();
				return;
			}
			bool ship = board->placeShip(x, y, i, (orientation == 'v') ?
				Board::Orientation::VERTICAL : Board::Orientation::HORIZONTAL);
			if (!ship) {
				invalidCommand(target);
				board->clear();
				return;
			}
		}
		target->getCurrentGame()->setReady(target->getIndex());
		target->sendMessage("ready");
	}

	void PlayerCommands::fire(Player* target, std::string args) {
		if (target->getCurrentGame() == nullptr || !target->getCurrentGame()->getTurn(target->getIndex())) {
			invalidCommand(target);
			return;
		}
		Board* board = target->getCurrentGame()->getBoard(1 - target->getIndex());
		if (board == nullptr) {
			invalidCommand(target);
			return;
		}
		std::stringstream argStream(args);
		int x, y;
		argStream >> x >> y;
		if (argStream.fail() || x < 0 || x >= board->getWidth() || y < 0 || y >= board->getHeight()) {
			invalidCommand(target);
			return;
		}
		int ship = board->hit(x, y);
		if (ship >= 0) {
			if (board->getShipState(ship) == Board::ShipState::SUNK) {
				target->sendMessage("sunk");
			}
			else {
				target->sendMessage("hit");
			}
		}
		else {
			target->sendMessage("miss");
		}
		target->getCurrentGame()->endTurn();
	}

	void PlayerCommands::invalidCommand(Player* target) {
		target->sendMessage("Invalid command");
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
		if (command.rfind("ships ", 0) == 0) {
			ships(target, command.substr(6));
			return;
		}
		if (command.rfind("fire ", 0) == 0) {
			fire(target, command.substr(5));
			return;
		}

		invalidCommand(target);
	}
}
