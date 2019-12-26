#include <BattleshipServer.h>

#define SERVER_PORT 2680

using namespace Sockets;
using namespace BattleshipServer;

int main() {
	ConnectionManager connectionManager;
	SocketBSD* server = new SocketBSD("", SERVER_PORT);
	server->listen();
	while (true) {
		connectionManager.handleConnection(server->accept());
	}
	server->close();
}
