#pragma once
#include <CommandParser.h>
#include <Matchmaker.h>

namespace BattleshipServer {

	/*
	Singleton command parser for a network player
	*/
	class PlayerCommands final : public CommandParser {

	private:
		Matchmaker matchmaker;

		PlayerCommands() = default;
		PlayerCommands(const PlayerCommands&) = delete;
		~PlayerCommands() = default;
		PlayerCommands& operator=(const PlayerCommands&) = delete;

		// Commands
		void match(Player* target);
		void leave(Player* target);

	public:
		// Gets instance of this singleton
		static PlayerCommands& instance();
		// Parses a command and applies its effect on the target
		virtual void parse(std::string command, Player* target) override;
	};
}
