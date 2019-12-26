#pragma once
#include <CommandParser.h>

namespace BattleshipServer {

	/*
	Singleton command parser for a network player
	*/
	class PlayerCommands final : public CommandParser {

	private:
		PlayerCommands() = default;
		PlayerCommands(const PlayerCommands&) = delete;
		~PlayerCommands() = default;
		PlayerCommands& operator=(const PlayerCommands&) = delete;

	public:
		// Gets instance of this singleton
		static PlayerCommands& instance();
		// Parses a command and applies its effect on the target
		virtual void parse(std::string command, Player* target) override;
	};
}
