#include "Player.h"

namespace BattleshipServer {

	Player::Player(Sockets::StringSocket& client, CommandParser& commandParser)
		:client(client), commandParser(commandParser) {}

	void Player::parseCommand(std::string command) {
		commandParser.parse(command, this);
	}
}
