#pragma once
#include <Socket.h>
#include <StringSocket.h>
#include <pthread.h>
#include <string>
#include <iostream>

namespace BattleshipServer {

	class ConnectionManager {

	private:
		static void* clientBehavior(void* client);

	public:
		void handleConnection(Sockets::Socket* client);
	};
}
