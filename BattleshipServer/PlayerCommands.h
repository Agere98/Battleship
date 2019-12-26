#pragma once
#include <CommandParser.h>

namespace BattleshipServer {

	class PlayerCommands final : public CommandParser {

	private:
		PlayerCommands() = default;
		PlayerCommands(const PlayerCommands&) = delete;
		~PlayerCommands() = default;
		PlayerCommands& operator=(const PlayerCommands&) = delete;

	public:
		static PlayerCommands& instance();
		virtual void parse(std::string command, Player* target) override;
	};
}
