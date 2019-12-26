#pragma once
#include <Socket.h>

namespace BattleshipServer {

	/*
	A class for managing client connections
	*/
	class ConnectionManager {

	private:
		static void* clientBehavior(void* client);

	public:
		// Creates a new thread for client behavior
		void handleConnection(Sockets::Socket* client);
	};
}
