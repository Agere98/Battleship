#pragma once
#include <Socket.h>

namespace BattleshipServer {

	class ConnectionManager {

	private:
		static void* clientBehavior(void* client);

	public:
		void handleConnection(Sockets::Socket* client);
	};
}
